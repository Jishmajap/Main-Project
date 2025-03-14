<template>
    <nav_stud></nav_stud>

    <div class="flex flex-row">
      <div class="ml-[20rem] mt-[2rem] w-full">
        <a href="#" class="block max-w-sm p-6 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-100 bg-gray-800 border-gray-700 hover:bg-gray-700">
          <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 text-white">Student Details:</h5>
          <div v-if="currentUser" class="flex flex-col">
            <div class="flex items-center">
              <p class="font-normal text-gray-700 dark:text-gray-400 mr-2"><b>Name:</b></p>
              <p class="font-normal text-gray-700 dark:text-gray-400">{{currentUser.firstName}} {{currentUser.lastName}}</p>
            </div>
            <div class="flex items-center">
              <p class="font-normal text-gray-700 dark:text-gray-400 mr-2"><b>College:</b></p>
              <p class="font-normal text-gray-700 dark:text-gray-400">{{currentUser.institution}}</p>
            </div>
          </div>
          <div v-else>
            <p class="font-normal text-gray-700 dark:text-gray-400">Loading user data...</p>
          </div>
        </a>
      </div>

      <div class="ml-[1rem] mt-[2rem] w-full">
        <a href="#" class="block max-w-sm p-6 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-100 bg-gray-800 border-gray-700 hover:bg-gray-700">
          <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 text-white">Account Status</h5>
          <div v-if="currentUser">
            <p class="font-normal text-gray-700 dark:text-gray-400"><b>Balance:</b></p>
            <p class="font-normal text-gray-700 dark:text-gray-400">{{currentUser.balance}}</p>
          </div>
          <div v-else>
            <p class="font-normal text-gray-700 dark:text-gray-400">Loading balance...</p>
          </div>
        </a>
      </div>
    </div>

    <div class=" ml-[20rem] mt-[2rem] w-[63rem]">
        <a href="#" class="block p-16 bg-gray-800 border border-gray-200 rounded-lg shadow-sm hover:bg-gray-100 bg-gray-800 border-gray-700 hover:bg-gray-700">
          <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 text-white">More Details</h5>
          <div v-if="currentUser" class="flex flex-col">
            <p class="font-normal text-gray-700 dark:text-gray-400"><b>College:</b> {{currentUser.institution}}</p>
            <p class="font-normal text-gray-700 dark:text-gray-400"><b>Districts:</b>{{currentUser.district}}</p>
            <p class="font-normal text-gray-700 dark:text-gray-400"><b>TagID:</b>{{currentUser.tagid}}</p>
            

          </div>
          <div v-else>
            <p class="font-normal text-gray-700 dark:text-gray-400">Loading details...</p>
          </div>
        </a>
      </div>
</template>

<script>
import nav_stud from '../components/nav_stud.vue'
import router from '../router';
import { collection, getDocs, getFirestore } from "firebase/firestore";
import { getAuth, onAuthStateChanged } from "firebase/auth";

export default {
  name: 'stud_dash',
  components: {
    nav_stud
  },
  data() {
    return {
      currentUser: null
    };
  },
  methods: {
    async fetchCurrentUserData(user) {
      try {
        if (!user) {
          console.log("User is not authenticated.");
          router.push('/login');
          return;
        }

        const db = getFirestore();
        const userEmail = user.email;

        const querySnapshot = await getDocs(collection(db, "student"));
        let found = false;
        querySnapshot.forEach((doc) => {
          const studentData = doc.data();

          if (studentData.email === userEmail) {
            console.log("Found matching student:", doc.id, studentData);
            this.currentUser = { id: doc.id, ...studentData };
            found = true;
          }
        });

        if (!found) {
          console.log("No student record found for the current user");
        }
      } catch (error) {
        console.error("Error fetching current user data:", error);
      }
    }
  },
  mounted() {
    const auth = getAuth();
    onAuthStateChanged(auth, (user) => {
      this.fetchCurrentUserData(user);
    });
  }
};
</script>
