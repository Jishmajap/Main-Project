#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include <MFRC522.h>
#include <SPI.h>
#include <vector>  // To store student IDs dynamically
#include <time.h>

#define SS_PIN 5   // ESP32 RFID
#define RST_PIN 22 // ESP32 RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

// WiFi credentials
#define WIFI_SSID "OPPOA76"
#define WIFI_PASSWORD "anushma1"

// Firebase credentials
#define API_KEY "AIzaSyCCKAu2Fwsii4jM5VqaNWVj0TVADXbAjHo"
#define FIREBASE_PROJECT_ID "dscc-9d323"

#define DEDUCTION_AMOUNT 5

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
std::vector<String> studentIDs;

// Function to get current timestamp in ISO 8601 format
String getCurrentTimestamp() {
    time_t now;
    time(&now);
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(buffer);
}

void fetchStudentIDs() {
    studentIDs.clear();
    String studentsPath = "student";

    if (Firebase.Firestore.listDocuments(&fbdo, 
                                         FIREBASE_PROJECT_ID, 
                                         "",
                                         studentsPath.c_str(),
                                         100,
                                         "",
                                         "",
                                         "",
                                         false)) {

        Serial.println("Raw response: " + fbdo.payload());

        FirebaseJson jsonResponse;
        jsonResponse.setJsonData(fbdo.payload());

        FirebaseJsonData documents;
        jsonResponse.get(documents, "documents");

        if (documents.success) {
            FirebaseJsonArray docArray;
            docArray.setJsonArrayData(documents.stringValue);

            for (size_t i = 0; i < docArray.size(); i++) {
                FirebaseJsonData docItem;
                docArray.get(docItem, i);

                FirebaseJson docJson;
                docJson.setJsonData(docItem.stringValue);

                FirebaseJsonData nameData;
                docJson.get(nameData, "name");

                if (nameData.success) {
                    String fullPath = nameData.stringValue;
                    int lastSlash = fullPath.lastIndexOf('/');
                    if (lastSlash != -1) {
                        String docID = fullPath.substring(lastSlash + 1);
                        studentIDs.push_back(docID);
                        Serial.println("Added student ID: " + docID);
                    }
                }
            }

            Serial.printf("Fetched %d student IDs from Firestore.\n", studentIDs.size());
        } else {
            Serial.println("Failed to parse documents array: " + fbdo.payload());
        }
    } else {
        Serial.println("Failed to fetch student IDs: " + fbdo.errorReason());
    }
}

void updateTapCount(const String& tagID) {
    String tapCountPath = "TagTapCount/" + tagID;

    // First, try to get the existing tap count
    int currentTapCount = 0;
    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", tapCountPath)) {
        FirebaseJson tapJson;
        tapJson.setJsonData(fbdo.payload());
        FirebaseJsonData tapCountData;

        if (tapJson.get(tapCountData, "fields/tapCount/integerValue")) {
            currentTapCount = tapCountData.intValue;
        }
    }

    // Increment tap count
    currentTapCount++;

    // Get current timestamp in correct format
    String currentTimestamp = getCurrentTimestamp();

    // Update tap count in Firebase
    FirebaseJson updateContent;
    updateContent.set("fields/tapCount/integerValue", currentTapCount);
    updateContent.set("fields/lastTapTimestamp/timestampValue", currentTimestamp);
    updateContent.set("fields/tapTime/stringValue", currentTimestamp);  // Store tap time as a separate field
    updateContent.set("fields/tagid/stringValue", tagID);

    if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", tapCountPath, updateContent.raw(), "tapCount,lastTapTimestamp,tapTime,tagid")) {
        Serial.printf("Tap count for tag %s updated to %d\n", tagID.c_str(), currentTapCount);
        Serial.printf("Tap time recorded: %s\n", currentTimestamp.c_str());
    } else {
        // If patch fails, create a new document
        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", tapCountPath, updateContent.raw())) {
            Serial.printf("Created new tap count entry for tag %s\n", tagID.c_str());
        } else {
            Serial.println("Failed to update or create tap count: " + fbdo.errorReason());
        }
    }
}

void setup() {
    Serial.begin(115200);
    SPI.begin();
    mfrc522.PCD_Init();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nConnected to Wi-Fi");

    // Configure time synchronization
    configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // Use multiple NTP servers

    config.api_key = API_KEY;
    config.token_status_callback = tokenStatusCallback;

    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("Firebase initialized successfully.");
    } else {
        Serial.printf("Firebase sign-up error: %s\n", config.signer.signupError.message.c_str());
    }

    Firebase.reconnectWiFi(true);
    Firebase.begin(&config, &auth);

    fetchStudentIDs();
}

void loop() {
    Serial.println("Waiting for RFID scan...");

    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        delay(500);
        return;
    }

    String tagID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        tagID += String(mfrc522.uid.uidByte[i], HEX);
    }
    tagID.toUpperCase();

    Serial.println("Scanned Tag ID: " + tagID);

    // Update tap count in Firebase
    updateTapCount(tagID);

    // Existing balance deduction logic remains the same
    String espDataPath = "EspData/" + tagID;

    bool tagExists = false;
    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", espDataPath)) {
        Serial.println("Tag ID found in EspData collection.");
        tagExists = true;
    } else {
        Serial.println("New tag detected. Storing in EspData collection...");

        FirebaseJson content;
        content.set("fields/tagid/stringValue", tagID);

        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", espDataPath, content.raw())) {
            Serial.println("Success! New tag ID saved to Firebase.");
            Serial.println(fbdo.payload());
            tagExists = true;
        } else {
            Serial.println("Failed uploading to Firebase: " + fbdo.errorReason());
        }
    }

    if (tagExists) {
        bool studentFound = false;
        String studentDocID = "";
        int currentBalance = 0;

        for (size_t i = 0; i < studentIDs.size(); i++) {
            String studentPath = "student/" + studentIDs[i];

            if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", studentPath)) {
                FirebaseJson studentJson;
                studentJson.setJsonData(fbdo.payload());
                FirebaseJsonData tagIdData;

                if (studentJson.get(tagIdData, "fields/tagid/stringValue") && 
                    tagIdData.stringValue.equalsIgnoreCase(tagID)) {
                    studentFound = true;
                    studentDocID = studentIDs[i];

                    FirebaseJsonData balanceData;
                    if (studentJson.get(balanceData, "fields/balance/integerValue")) {
                        currentBalance = balanceData.intValue;
                        Serial.printf("Found student with matching tag ID. Current balance: %d\n", currentBalance);

                        if (currentBalance < DEDUCTION_AMOUNT) {
                            Serial.println("Insufficient balance. Scan rejected.");
                            return;
                        }

                        break;
                    } else {
                        Serial.println("Balance field not found or not in expected format");
                    }
                }
            }
        }

        if (studentFound) {
            int newBalance = currentBalance - DEDUCTION_AMOUNT;
            FirebaseJson updateContent;
            updateContent.set("fields/balance/integerValue", newBalance);

            String studentPath = "student/" + studentDocID;
            if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", studentPath, updateContent.raw(), "balance")) {
                Serial.printf("Balance successfully reduced by %d units.\n", DEDUCTION_AMOUNT);
            } else {
                Serial.println("Failed to update balance: " + fbdo.errorReason());
            }
        } else {
            Serial.println("No student found with this tag ID.");
        }
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    delay(2000);
}