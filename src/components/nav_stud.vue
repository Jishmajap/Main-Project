<template>
  <div class="fixed left-0 top-0 w-64 h-full bg-[#f8f4f3] p-4 z-50 sidebar-menu transition-transform">
    
    <a href="#" class="flex items-center pb-4 pt-4 border-b border-b-gray-800">
      <h2 class="font-bold text-2xl">Student <span class="bg-gray-700 text-white px-2 rounded-md">Card</span></h2>
    </a>

    <ul class="mt-4">
      <span class="text-gray-400 font-bold">STUDENTS</span>
      <li class="mb-1 group">
        <a href="/stud_dash" class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md">
          <i class="ri-home-2-line mr-3 text-lg"></i>
          <span class="text-sm">DASHBOARD</span>
        </a>
      </li>
      <li class="mb-1 group">
        <a href="/request" class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md">
          <i class='bx bx-user mr-3 text-lg'></i>
          <span class="text-sm">RECHARGE</span>
        </a>
      </li>
      
      <!-- Logout Button -->
      <li class="mb-1 group">
        <a @click="logout" href="javascript:void(0);" class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md">
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
  name: 'nav_stud',
  methods: {
    async logout() {
      const auth = getAuth();

      try {
        await signOut(auth);  // Properly logs the user out from Firebase
        localStorage.clear(); // Clear all local storage data
        sessionStorage.clear(); // Clear session data as well

        // Redirect to the login page
        window.location.href = '/'; 
      } catch (error) {
        console.error('Logout failed:', error.message);
        alert('Failed to log out. Please try again.');
      }
    }
  }
}
</script>
