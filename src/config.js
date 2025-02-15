
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getFirestore,doc,getDoc } from "firebase/firestore";
import { getAuth } from "firebase/auth";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyCCKAu2Fwsii4jM5VqaNWVj0TVADXbAjHo",
  authDomain: "dscc-9d323.firebaseapp.com",
  projectId: "dscc-9d323",
  storageBucket: "dscc-9d323.firebasestorage.app",
  messagingSenderId: "1004252039395",
  appId: "1:1004252039395:web:10b7ea02ea6d067c565dd6",
  measurementId: "G-PYWRYR0K3M"
};

const app= initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const db = getFirestore(app);
const auth = getAuth(app);
export {db,auth};