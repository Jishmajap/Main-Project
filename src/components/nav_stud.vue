<template>
   
    <div class="fixed left-0 top-0 w-64 h-full bg-[#f8f4f3] p-4 z-50 sidebar-menu transition-transform">
     <a href="#" class="flex items-center pb-4 border-b border-b-gray-800">
 
       <h2 class="font-bold text-2xl">Student <span class="bg-gray-700 text-white px-2 rounded-md">Card</span>
       </h2>
     </a>
     <ul class="mt-4">
       <span class="text-gray-400 font-bold">STUDENTS</span>
       <li class="mb-1 group">
         <a href="/stud_dash"
           class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100">
           <i class="ri-home-2-line mr-3 text-lg"></i>
           <span class="text-sm">DASHBOARD</span>
         </a>
       </li>
       <li class="mb-1 group">
         <a href="/request"
           class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100 sidebar-dropdown-toggle">
           <i class='bx bx-user mr-3 text-lg'></i>
           <span class="text-sm">RECHARGE</span>
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
       
       <li class="mb-1 group">
        <a href=""
          class="flex font-semibold items-center py-2 px-4 text-gray-900 hover:bg-gray-950 hover:text-gray-100 rounded-md group-[.active]:bg-gray-800 group-[.active]:text-white group-[.selected]:bg-gray-950 group-[.selected]:text-gray-100">
          <i class='bx bx-archive mr-3 text-lg'></i>
          <span class="text-sm">LOGOUT</span>
        </a>
      </li>
      
       
       
     </ul>
   </div>
   <div class="fixed top-0 left-0 w-full h-full bg-black/50 z-40 md:hidden sidebar-overlay"></div>
 
 </template>
 <script>
 export default{
 
     name:'nav_stud',
     components: {
         data(){ 
         return{
 
         }
              }
         }
 
 }
 </script>
 