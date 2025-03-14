<template>
  <navigation />
  <a href="/view_details">
    <button type="submit"
      class="text-white bg-gray-900 hover:bg-gray-800 focus:ring-4 focus:outline-none focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 border border-neutral-900 flex items-center justify-center space-x-2 ml-[85rem] mt-[1rem]">
      <svg class="w-6 h-6 text-white" aria-hidden="true" xmlns="http://www.w3.org/2000/svg" fill="none"
        viewBox="0 0 24 24">
        <path stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
          d="M5 12h14m-7 7V5" />
      </svg>
      <span>ADD</span>
    </button>
  </a>
  <br />

  <div class="ml-[17rem] mt-[1rem] relative sm:rounded-lg">
    <table class="w-full text-sm text-left rtl:text-right text-gray-900 border">
      <tr class="border"> 
        <th>Id</th>
        <th>FirstName</th>
        <th>lastName</th>
        <th>Email</th>
        <th>Institution</th>
        <th>Status</th>
        <th>TagID</th>
      </tr>
      <tr v-for="user in users" :key="user.id" class="border">
        <td>{{ user.id }}</td>
        <td>{{ user.firstName }}</td>
        <td>{{ user.lastName }}</td>
        <td>{{ user.email }}</td>
        <td>{{ user.institution }}</td>
        <td>{{ user.status }}</td>
        <td>{{ user.tagid }}</td>
      </tr>
    </table>
  </div>
</template>

<script>
import navigation from '../components/navigation.vue';
import { collection, getDocs, getFirestore } from "firebase/firestore";
 import router from '../router';
import isLogin from '../utils/userValidation'

export default {
  name: 'students',
  components: {
    navigation
  },
  data() {
    return {
      users: []
    };
  },
  methods: {
    async fetchStudentData() {
      try {
        const db = getFirestore();
        const querySnapshot = await getDocs(collection(db, "student"));
        if (querySnapshot.empty) {
          console.log("No documents found in the 'students' collection.");
        } else {
          querySnapshot.forEach((doc) => {
            console.log("Fetched document:", doc.id, doc.data());
            this.users.push({ id: doc.id, ...doc.data() });
          });
          console.log("All fetched users:", this.users);
        }
      } catch (error) {
        console.error("Error fetching student data:", error);
      }
    }
  },
  mounted() {
    this.fetchStudentData();
  },
  beforeMount(){       
        if(isLogin()===true){
            router.push('/stud_login')
        }
    }
};

</script>