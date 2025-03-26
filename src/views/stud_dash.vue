<template>
  <nav_stud />

  <div class="flex flex-row">
    <!-- Student Details Section -->
    <div class="ml-[20rem] mt-[2rem] w-full">
      <a href="#" class="block max-w-sm p-6 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-700">
        <h5 class="mb-2 text-2xl font-bold tracking-tight text-white">Student Details:</h5>
        <div v-if="currentUser" class="flex flex-col">
          <div class="flex items-center">
            <p class="font-normal text-gray-400 mr-2"><b>Name:</b></p>
            <p class="font-normal text-gray-400">{{ currentUser.firstName }} {{ currentUser.lastName }}</p>
          </div>
          <div class="flex items-center">
            <p class="font-normal text-gray-400 mr-2"><b>College:</b></p>
            <p class="font-normal text-gray-400">{{ currentUser.institution }}</p>
          </div>
        </div>
        <div v-else>
          <p class="font-normal text-gray-400">Loading user data...</p>
        </div>
      </a>
    </div>

    <!-- Account Status Section -->
    <div class="ml-[1rem] mt-[2rem] w-full">
      <a href="#" class="block max-w-sm p-6 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-700">
        <h5 class="mb-2 text-2xl font-bold tracking-tight text-white">Account Status</h5>
        <div v-if="currentUser">
          <p class="font-normal text-gray-400"><b>Balance:</b> {{ currentUser.balance }}</p>
        </div>
        <div v-else>
          <p class="font-normal text-gray-400">Loading balance...</p>
        </div>
      </a>
    </div>
  </div>

  <!-- More Details Section -->
  <div class="ml-[20rem] mt-[2rem] w-[63rem]">
    <a href="#" class="block p-16 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-700">
      <h5 class="mb-2 text-2xl font-bold tracking-tight text-white">More Details</h5>
      <div v-if="currentUser" class="flex flex-col">
        <p class="font-normal text-gray-400"><b>College:</b> {{ currentUser.institution }}</p>
        <p class="font-normal text-gray-400"><b>District:</b> {{ currentUser.district }}</p>
        <p class="font-normal text-gray-400"><b>TagID:</b> {{ currentUser.tagid }}</p>
      </div>
      <div v-else>
        <p class="font-normal text-gray-400">Loading details...</p>
      </div>
    </a>
  </div>
</template>

<script>
import nav_stud from "../components/nav_stud.vue";
import router from "../router";
import { collection, query, where, getDocs, getFirestore } from "firebase/firestore";
import { getAuth, onAuthStateChanged } from "firebase/auth";

export default {
  name: "stud_dash",
  components: {
    nav_stud,
  },
  data() {
    return {
      currentUser: null, // Stores the currently logged-in user's data
    };
  },
  methods: {
    // Fetch data for the logged-in student
    async fetchCurrentUserData(user) {
      try {
        const db = getFirestore();
        const userEmail = user.email; // Get the user's email

        console.log("Fetching data for user email:", userEmail);
        

        // Query Firestore for a student record matching the user's email
        const studentQuery = query(
          collection(db, "student"),
          where("email", "==", userEmail)
        );
        const querySnapshot = await getDocs(studentQuery);

        if (!querySnapshot.empty) {
          const studentDoc = querySnapshot.docs[0]; // Use the first matching document
          const studentData = studentDoc.data();

            console.log("Logged in as student:", studentDoc.id, studentData);
            this.currentUser = { id: studentDoc.id, ...studentData }; // Save student data to state
          
        } else {
          console.warn("No student record found for email:", userEmail);
          router.push("/"); // Redirect if no record found
        }
      } catch (error) {
        console.error("Error fetching current user data:", error.message);
      }
    },
  },
  mounted() {
    const auth = getAuth();
    // Listen for authentication state changes
    onAuthStateChanged(auth, (user) => {
      if (user) {
        console.log("Authenticated user:", user.email);
        this.fetchCurrentUserData(user); // Fetch the logged-in student's data
      } else {
        console.log("No authenticated user.");
        router.push("/"); // Redirect to login if unauthenticated
      }
    });
  },
};
</script>

