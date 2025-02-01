<template>
  
   
    <div class="flex items-center justify-center h-screen b">
    
    <div class="w-full max-w-sm p-4 bg-gray-800 border border-gray-200 rounded-lg shadow sm:p-6 md:p-8 y">
        <form class="space-y-6" action="#">
            <h5 class="text-3xl font-medium text-gray-900  content-center text-center text-white pt-[2rem] "><b>Login</b></h5>
            <div>
                <label for="id" class="block mb-2 text-sm font-medium text-gray-900 dark:text-white">Student ID</label>
                <input type="text" name="stud_id" id="stud_id" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 dark:border-gray-500 dark:placeholder-gray-400 " placeholder="Enter valid ID" required />
            </div>
            <div>
                <label for="password" class="block mb-2 text-sm font-medium text-gray-900 dark:text-white"> Password</label>
                <input type="password" name="password" id="password" placeholder="••••••••" class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 dark:border-gray-500 dark:placeholder-gray-400 " required />
            </div>
            <div class="flex items-start">
                
            </div>
            <button type="submit" class="w-full text-white bg-blue-500  focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-400 dark:focus:ring-blue-800 " href="/stud_bal">Login</button>
            <div class="text-sm font-medium text-gray-500 dark:text-gray-300 pb-[2rem] text-center">
                Not registered? <a href="#" class="text-blue-700 hover:underline dark:text-blue-500">Create account</a>
            </div>
        </form>
    </div>
    </div>
    
</template>
    
 <script>
     
</script>
    
    