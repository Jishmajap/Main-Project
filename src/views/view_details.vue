<template>
    <navigation />

    <section class="bg-gray-50 ">
        <div class="flex flex-col items-center justify-center px-6 py-8 mx-auto md:h-screen lg:py-0 bg-gray-200 w-full">
            <div class="w-full rounded-lg shadow dark:border md:mt-0 sm:max-w-md xl:p-0 bg-[#f8f4f3]">
                <div class="p-6 space-y-4 md:space-y-6 sm:p-8">
                    <h1 class="text-xl font-bold leading-tight tracking-tight text-gray-900 md:text-2xl text-black text-center text-black">
                        ADD NEW STUDENT
                    </h1>
                    <form class="space-y-4 md:space-y-6" @submit.prevent="handleSubmit">
                        <div class="grid md:grid-cols-2 md:gap-6">
                            <div class="relative z-0 w-full mb-5 group">
                                <input type="text" name="floating_first_name" id="floating_first_name" v-model="formData.firstName"
                                    class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                    placeholder=" " required />
                                <label for="floating_first_name"
                                    class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">First
                                    name</label>
                            </div>
                            <div class="relative z-0 w-full mb-5 group">
                                <input type="text" name="floating_last_name" id="floating_last_name" v-model="formData.lastName"
                                    class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                    placeholder=" " required />
                                <label for="floating_last_name"
                                    class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">Last
                                    name</label>
                            </div>
                        </div>
                        <div class="relative z-0 w-full mb-5 group">
                            <input type="text" name="institution" id="floating_institution" v-model="formData.institution"
                                class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                placeholder=" " required />
                            <label for="institution"
                                class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">Name
                                of Institution</label>
                        </div>
                        <div class="relative z-0 w-full mb-5 group">
                            <input type="text" name="institution" id="floating_institution" v-model="formData.district"
                                class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                placeholder=" " required />
                            <label for="institution"
                                class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">District
                                </label>
                        </div>
                        <div class="relative z-0 w-full mb-5 group">
                            <input type="email" name="floating_email" id="floating_email" v-model="formData.email"
                                class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                placeholder=" " required />
                            <label for="floating_email"
                                class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 rtl:peer-focus:left-auto peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">Email
                                address</label>
                         </div>
                      <!--Dropdown-->
                        <div class="relative z-0 w-full mb-5 group">
                             <label for="tagID" class="text-white">Tag ID</label>
                             <select id="tagID" v-model="formData.tagid" class="text-white bg-gray-800 hover:bg-gray-700 font-medium rounded-lg text-sm px-5 py-2.5 w-full">
                             <option value="" disabled selected>Select Tag ID</option>
                             <option v-for="item in dropdownItems" :key="item.id" :value="item.id">{{ item.id }}</option>
                             </select>
                        </div>
                        <!--password-->
                        <div class="relative z-0 w-full mb-5 group">
                            <input type="password" name="repeat_password" id="floating_repeat_password" v-model="formData.password"
                                class="block py-2.5 px-0 w-full text-sm text-gray-900 bg-transparent border-0 border-b-2 border-gray-300 appearance-none dark:border-gray-600 dark:focus:border-blue-500 focus:outline-none focus:ring-0 focus:border-blue-600 peer"
                                placeholder=" " required />
                            <label for="floating_repeat_password"
                                class="peer-focus:font-medium absolute text-sm text-gray-500 dark:text-gray-400 duration-300 transform -translate-y-6 scale-75 top-3 -z-10 origin-[0] peer-focus:start-0 rtl:peer-focus:translate-x-1/4 peer-focus:text-blue-600 peer-focus:dark:text-blue-500 peer-placeholder-shown:scale-100 peer-placeholder-shown:translate-y-0 peer-focus:scale-75 peer-focus:-translate-y-6">
                                password</label>
                        </div>

                        <div class="flex items-start">
                            <p v-if="error" class="text-red-400">{{ error }}</p>
                        </div>

                        <button type="submit" 
                            class="w-full text-white bg-gray-900 hover:bg-gray-800 focus:ring-4 focus:outline-none focus:ring-primary-300 font-medium rounded-lg text-sm px-5 py-2.5 border border-neutral-900 flex items-center justify-center space-x-2">
                            <svg class="w-6 h-6 text-white" aria-hidden="true" xmlns="http://www.w3.org/2000/svg"
                                fill="none" viewBox="0 0 24 24">
                                <path stroke="currentColor" stroke-linecap="round" stroke-linejoin="round"
                                    stroke-width="2" d="M5 12h14m-7 7V5" />
                            </svg>
                            <span>ADD</span>
                        </button>
                    </form>
                </div>
            </div>
        </div>
    </section>
</template>

<script>
import { ref, onMounted } from 'vue'
import { db } from '../config'
import { collection, addDoc, getDocs, deleteDoc, doc, onSnapshot } from 'firebase/firestore'
import navigation from '../components/navigation.vue'
import { getAuth, createUserWithEmailAndPassword, onAuthStateChanged } from "firebase/auth";
import router from '../router';
import isLogin from '../utils/userValidation'

const auth = getAuth();

export default {
    name: 'view_details',
    components: {
        navigation
    },
    setup() {
        const users = ref([])
        const formData = ref({
            firstName: '',
            lastName: '',
            institution: '',
            district:'',
            email: '',
            tagid:'',
            password: ''
        })
        const confirmpassword = ref('')
        const error = ref('')
        const isDropdownOpen = ref(false)
        const dropdownItems = ref([])

        const toggleDropdown = () => {
            isDropdownOpen.value = !isDropdownOpen.value
        }

        // Add user to database
        const handleSubmit = async () => {
            console.log("hello");
            try {
                console.log("Form data before sending:", formData.value) // Log form data before sending
                console.log(formData.value.email,"pass:  ", formData.value.password);
                
                await createUserWithEmailAndPassword(auth, formData.value.email, formData.value.password)
                await addDoc(collection(db, 'student'), {
                    firstName: formData.value.firstName,
                    lastName: formData.value.lastName,
                    institution: formData.value.institution,
                    district: formData.value.district,
                    email: formData.value.email,
                    tagid: formData.value.tagid,
                    password: formData.value.password
                })
                console.log("Document successfully added!") // Log success message
                formData.value = { firstName: '', lastName: '', institution: '',district:'', email: '',tagid:'', password: '' }
            } catch (err) {
                console.error("Error adding document: ", err)
                error.value = "Error adding document"
            }
        }

        // Fetch data from database
        const fetchDropdownItems = async () => {
            try {
                const querySnapshot = await getDocs(collection(db, "EspData"));
                const studentSnapshot = await getDocs(collection(db, "student"));

                const existingTagIds = studentSnapshot.docs.map(doc => doc.data().tagid);

                dropdownItems.value = querySnapshot.docs
                    .map(doc => ({
                        id: doc.id, 
                        ...doc.data()
                    }))
                    .filter(item => !existingTagIds.includes(item.id));

                console.log(dropdownItems.value);
            } catch (err) {
                console.error("Error fetching dropdown items: ", err);
            }
        }


        // Delete user from database
        const deleteUser = async (id) => {
            try {
                await deleteDoc(doc(db, 'student', id))
            } catch (err) {
                console.error("Error deleting document: ", err)
                error.value = "Error deleting document"
            }
        }

        // Real-time updates
        onMounted(() => {
            const auth = getAuth();
            // Listen for authentication state changes
            onAuthStateChanged(auth, (user) => {
            if (!user) {
                console.log("No authenticated user.");
                router.push("/"); // Redirect to login if unauthenticated
            }
            });
            fetchDropdownItems();
            const unsubscribe = onSnapshot(collection(db, 'student'), (snapshot) => {
                users.value = snapshot.docs.map(doc => ({
                    id: doc.id,
                    ...doc.data()
                }))
            })
        })

        return {
            users,
            formData,
            confirmpassword,
            error,
            handleSubmit,
            deleteUser,
            isDropdownOpen,
            toggleDropdown,
            dropdownItems
        }
    },
    beforeMount(){       
        if(isLogin()===true){
            router.push('/stud_login')
        }
    }
}
</script>

<style>
#dropdownDefaultButton {
    background-color: rgba(17, 24, 39);
}
</style>