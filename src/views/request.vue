<template>
    <nav_stud></nav_stud>

    <!-- Balance display -->
    <div class="bg-[#f8f4f3] p-10 border-gray-200 rounded-lg shadow-sm border-gray-700 w-[30rem] ml-[20rem] mt-[5rem]">
        <a href="#">
            <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900">Balance</h5>
        </a>
        <p class="mb-3 font-normal text-gray-700 text-gray-400">{{ currentBalance }}</p>
    </div>

    <!-- Add Balance Form -->
    <div class="w-[30rem] p-6 bg-[#f8f4f3] border-gray-200 rounded-lg shadow-sm border-gray-700 ml-[20rem] mt-[2rem]">
        <a href="#">
            <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900">ADD Balance</h5>
        </a>
        <div class="mb-6">
            <input 
                type="number" 
                id="balance" 
                v-model="formData.balance" 
                class="bg-gray-50 border border-gray-300 text-gray-900 text-sm rounded-lg focus:ring-blue-500 focus:border-blue-500 block w-full p-2.5 dark:bg-gray-700 dark:border-gray-600 dark:placeholder-gray-400 dark:focus:ring-blue-500 dark:focus:border-blue-500" 
                placeholder="Enter your balance" 
                required 
            />
        </div>

        <button 
            type="button" 
            @click="handleAddBalance"
            class="text-white bg-gray-900 hover:bg-gray-800 font-medium rounded-lg text-sm px-5 py-2.5 inline-flex justify-center text-center">
            ADD
        </button>
    </div>
</template>

<script>
import { onAuthStateChanged } from 'firebase/auth';
import nav_stud from '../components/nav_stud.vue';
import router from '../router';
import { ref } from 'vue';
import { db, auth } from '../config.js';
import { updateDoc, doc, getDocs, collection, query, where } from 'firebase/firestore';
import isLogin from '../utils/userValidation';

export default {
    name: 'request',
    components: {
        nav_stud
    },
    beforeMount() {
        if (isLogin() === true) {
            router.push('/stud_login');
        }
    },
    setup() {
        const formData = ref({
            balance: ''
        });
        const currentBalance = ref(0);

        let userEmail = null;

        onAuthStateChanged(auth, async (user) => {
            if (user) {
                userEmail = user.email;
                console.log('Authenticated user email:', userEmail);
                await fetchCurrentBalance();
            } else {
                console.warn('No user logged in');
                router.push('/stud_login');
            }
        });

        const fetchCurrentBalance = async () => {
            if (!userEmail) return;

            const q = query(collection(db, 'student'), where('email', '==', userEmail));
            const querySnapshot = await getDocs(q);

            if (!querySnapshot.empty) {
                currentBalance.value = querySnapshot.docs[0].data().balance || 0;
            }
        };

        const handleAddBalance = async () => {
            if (formData.value.balance === '' || isNaN(formData.value.balance) || formData.value.balance < 0) {
                alert('Please enter a valid balance');
                return;
            }

            if (!userEmail) {
                alert('No user found. Please log in.');
                return;
            }

            try {
                const q = query(collection(db, 'student'), where('email', '==', userEmail));
                const querySnapshot = await getDocs(q);

                if (!querySnapshot.empty) {
                    const userDoc = querySnapshot.docs[0].ref;
                    const newBalance = Number(currentBalance.value) + Number(formData.value.balance);
                    await updateDoc(userDoc, { balance: newBalance });

                    currentBalance.value = newBalance;
                    alert('Balance updated successfully!');
                    formData.value.balance = '';
                } else {
                    alert('No document found for the logged-in user.');
                }
            } catch (err) {
                console.error('Error updating balance:', err.message);
                alert(`Error updating balance: ${err.message}`);
            }
        };

        return {
            formData,
            handleAddBalance,
            currentBalance
        };
    }
};
</script>
