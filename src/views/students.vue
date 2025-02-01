<template>
    <navigation/>
<a href="/view_details">
<button type="submit"
  class="text-white bg-gray-900 hover:bg-gray-800 focus:ring-4 focus:outline-none focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 border border-neutral-900 flex items-center justify-center space-x-2 ml-[85rem] mt-[1rem]">
  <svg class="w-6 h-6 text-white"aria-hidden="true"xmlns="http://www.w3.org/2000/svg"fill="none"viewBox="0 0 24 24">
    <path
      stroke="currentColor"
      stroke-linecap="round"
      stroke-linejoin="round"
      stroke-width="2"
      d="M5 12h14m-7 7V5"
    />
  </svg>
  <span>ADD</span>
</button>
</a>




    
</template>

<script>
  import navigation from '../components/navigation.vue'
   export default{ 
    name:'students',
    components: {
        navigation
    
    }
}
</script>