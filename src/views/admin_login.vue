<template>
    <div class="flex items-center justify-center h-screen">
      <div class="w-full max-w-sm p-4 bg-gray-800 border border-gray-200 rounded-lg shadow sm:p-6 md:p-8">
        <form class="space-y-6" @submit.prevent="handleSubmit">
          <h5 class="text-3xl font-medium text-white text-center pt-[2rem]">
            <b>Login</b>
          </h5>
          <div>
            <label for="email" class="block mb-2 text-sm font-medium text-white">Email</label>
            <input
              type="email"
              v-model="email"
              id="email"
              class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 dark:border-gray-500 dark:placeholder-gray-400"
              placeholder="name@example.com"
              required
            />
          </div>
          <div>
            <label for="password" class="block mb-2 text-sm font-medium text-white">Password</label>
            <div class="relative">
              <input
                :type="showPassword ? 'text' : 'password'"
                v-model="password"
                id="password"
                class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 border-gray-500 dark:placeholder-gray-400"
                placeholder="••••••••"
                required
              />
              <button
                type="button"
                @click="togglePassword"
                class="absolute inset-y-0 right-0 flex items-center pr-3 text-gray-500 text-gray-500"
              >
                <svg
                  v-if="showPassword"
                  xmlns="http://www.w3.org/2000/svg"
                  class="h-5 w-5"
                  fill="none"
                  viewBox="0 0 24 24"
                  stroke="currentColor"
                  stroke-width="2"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M13.875 18.825A10.05 10.05 0 0112 19c-5.523 0-10-4.477-10-10S6.477 0 12 0c2.343 0 4.515.802 6.25 2.125M15.875 6.175A3.501 3.501 0 0118 9c0 1.657-1.004 3.034-2.4 3.625"
                  />
                </svg>
                <svg
                  v-else
                  xmlns="http://www.w3.org/2000/svg"
                  class="h-5 w-5"
                  fill="none"
                  viewBox="0 0 24 24"
                  stroke="currentColor"
                  stroke-width="2"
                >
                  <path
                    stroke-linecap="round"
                    stroke-linejoin="round"
                    d="M3.98 8.708A10.025 10.025 0 002.27 10.5C3.892 13.26 6.65 15.5 10 15.5c2.04 0 3.92-.61 5.5-1.643M9.828 12.684a3.505 3.505 0 014.828-4.828M10 5a3.5 3.5 0 013.5 3.5c0 .86-.31 1.64-.828 2.228"
                  />
                </svg>
              </button>
            </div>
          </div>
          <div class="flex items-start">
            <p v-if="error" class="text-red-400">{{ error }}</p>
          </div>
          <button
            type="submit"
            class="w-full text-white bg-blue-500 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm px-5 py-2.5 text-center dark:bg-blue-600 dark:hover:bg-blue-400 dark:focus:ring-blue-800"
          >
            Login
          </button>
          <div class="text-sm font-medium text-gray-500 dark:text-gray-300 pb-[2rem] text-center">
            Not registered?
            <a href="/signup_admin" class="text-blue-700 hover:underline dark:text-blue-500">Create account</a>
          </div>
        </form>
      </div>
    </div>
  </template>
  
  <script setup>
  import { ref } from "vue";
  import { auth } from "../config";
  import { signInWithEmailAndPassword } from "firebase/auth";
  import { useRouter } from "vue-router";
  
  const email = ref("");
  const password = ref("");
  const error = ref("");
  const showPassword = ref(false);
  const router = useRouter();
  
  const handleSubmit = async () => {
    try {
      await signInWithEmailAndPassword(auth, email.value, password.value);
      localStorage.setItem("isLogin", "true");
      router.push("/dashboard");
    } catch (err) {
      switch (err.code) {
        case "auth/invalid-credential":
          error.value = "Invalid email or password";
          break;
        case "auth/user-not-found":
          error.value = "No account found with this email";
          break;
        case "auth/wrong-password":
          error.value = "Incorrect password";
          break;
        default:
          error.value = "Something went wrong";
      }
    }
  };
  
  const togglePassword = () => {
    showPassword.value = !showPassword.value;
  };
  </script>
  