<template>
  <div class="fixed left-0 top-0 w-64 h-full bg-[#f8f4f3] p-4 z-50 sidebar-menu transition-transform">
    <a href="#" class="flex items-center pb-4 border-b border-b-gray-800">
      <h2 class="font-bold text-2xl">Student <span class="bg-gray-700 text-white px-2 rounded-md">Card</span>
      </h2>
    </a>

    <ul class="mt-4">
      <span class="text-gray-400 font-bold">ADMIN</span>
      <li class="mb-1 group">
        <a href="/dashboard"
          class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100">
          <i class="ri-home-2-line mr-3 text-lg"></i>
          <span class="text-sm">Dashboard</span>
        </a>
      </li>

      <li class="mb-1 group">
        <a href="/students"
          class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100 sidebar-dropdown-toggle">
          <i class='bx bx-user mr-3 text-lg'></i>
          <span class="text-sm">Students</span>
          <i class="ri-arrow-right-s-line ml-auto group-[.selected]:rotate-90"></i>
        </a>

        <ul class="pl-7 mt-2 hidden group-[.selected]:block">
          <li class="mb-4">
            <a href=""
              class="text-gray-900 text-sm flex items-center hover:text-[#f84525] before:contents-[''] before:w-1 before:h-1 before:rounded-full before:bg-gray-300 before:mr-3">All</a>
          </li>
          <li class="mb-4">
            <a href=""
              class="text-gray-900 text-sm flex items-center hover:text-[#f84525] before:contents-[''] before:w-1 before:h-1 before:rounded-full before:bg-gray-300 before:mr-3">Roles</a>
          </li>
        </ul>
      </li>

      <!-- <li class="mb-1 group">
        <a href="/analytics"
          class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100 sidebar-dropdown-toggle">
          <i class='bx bxl-blogger mr-3 text-lg'></i>
          <span class="text-sm">Analytics</span>
          <i class="ri-arrow-right-s-line ml-auto group-[.selected]:rotate-90"></i>
        </a>
      </li> -->

      <li class="mb-1 group">
        <a @click="logout" href="javascript:void(0);"
          class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md">
          <i class='bx bx-archive mr-3 text-lg'></i>
          <span class="text-sm">LOGOUT</span>
        </a>
      </li>
    </ul>
  </div>

  <div class="fixed top-0 left-0 w-full h-full bg-black/50 z-40 md:hidden sidebar-overlay"></div>
</template>

<script>
import { getAuth, signOut } from 'firebase/auth';

export default {
  name: 'navigation',
  methods: {
    async logout() {
      const auth = getAuth();

      try {
        await signOut(auth);  // Properly logs the user out from Firebase
        localStorage.clear(); // Clear all local storage data
        sessionStorage.clear(); // Clear session data as well

        // Correct redirection to '/'
        window.location.href = '/'; 
      } catch (error) {
        console.error('Logout failed:', error.message);
        alert('Failed to log out. Please try again.');
      }
    }
  }
}
</script>