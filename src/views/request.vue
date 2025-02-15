<template>
    <nav_stud></nav_stud>

   
    </template>
    <script>
    import nav_stud from '../components/nav_stud.vue'
    import router from '../router';
import isLogin from '../utils/userValidation'
    
    export default{
        name:'request',
        components: {
            nav_stud
        },
        beforeMount(){       
        if(isLogin()===true){
            router.push('/stud_login')
        }
    }
    }
    </script>