<template>
  <div class="flex items-center justify-center h-screen">
    <div class="w-full max-w-sm p-4 bg-gray-800 border border-gray-200 rounded-lg shadow sm:p-6 md:p-8">
      <form class="space-y-6" @submit.prevent="handleSubmit">
        <h5 class="text-3xl font-medium text-white text-center pt-[2rem]">
          <b>Login</b>
        </h5>

        <div class="relative z-0 w-full mb-5 group">
          <select
            v-model="userType"
            class="text-white bg-gray-900 hover:bg-gray-700 font-medium rounded-lg text-sm px-5 py-2.5 w-full"
          >
            <option value="admin">Admin</option>
            <option value="student">Student</option>
          </select>
        </div>

        <div>
          <label
            :for="userType === 'admin' ? 'email' : 'stud_id'"
            class="block mb-2 text-sm font-medium text-white"
          >
            {{ userType === 'admin' ? 'Email' : 'Student ID' }}
          </label>
          <input
            :type="userType === 'admin' ? 'email' : 'text'"
            v-model="email"
            :id="userType === 'admin' ? 'email' : 'stud_id'"
            class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 dark:border-gray-500 dark:placeholder-gray-400"
            :placeholder="userType === 'admin' ? 'name@example.com' : 'Enter valid ID'"
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
              class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-600 dark:border-gray-500 dark:placeholder-gray-400"
              placeholder="••••••••"
              required
            />
            <button
              type="button"
              @click="togglePassword"
              class="absolute inset-y-0 right-0 flex items-center pr-3 text-gray-500 dark:text-gray-300"
              aria-label="Toggle password visibility"
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
      </form>
    </div>
  </div>
</template>

<script setup>
import { ref } from "vue";
import { auth } from "../config";
import { signInWithEmailAndPassword } from "firebase/auth";
import { getFirestore, collection, getDocs, query, where } from "firebase/firestore";
import { useRouter } from "vue-router";

const email = ref("");
const password = ref("");
const error = ref("");
const showPassword = ref(false);
const userType = ref("admin"); // Default to admin
const router = useRouter();

const handleSubmit = async () => {
  try {
    if (userType.value === "admin") {
      await signInWithEmailAndPassword(auth, email.value, password.value);
      localStorage.setItem("isLogin", "true");
      localStorage.setItem("userType", "admin");
      router.push("/dashboard");
    } 
    
    else if (userType.value === "student") {

      const db = getFirestore();
      await signInWithEmailAndPassword(auth, email.value, password.value);

      const studentQuery = query(
        collection(db, "student"),
        where("email", "==", email.value),
        where("password", "==", password.value)
      );

      const querySnapshot = await getDocs(studentQuery);

      if (!querySnapshot.empty) {
        const studentData = querySnapshot.docs[0].data();
        localStorage.setItem("isLogin", "true");
        localStorage.setItem("userType", "student");
        localStorage.setItem("studentData", JSON.stringify(studentData));
        router.push("/stud_dash");
      } else {
        error.value = "Invalid student credentials";
      }
    }
  } catch (err) {
    error.value = err.code === "auth/user-not-found" ? "User not found" : "Something went wrong";
  }
};

const togglePassword = () => {
  showPassword.value = !showPassword.value;
};
</script>
