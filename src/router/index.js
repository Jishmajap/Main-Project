
import { createWebHistory, createRouter } from 'vue-router'

 import login from '../views/login.vue'
 import analytics from '../views/analytics.vue'
 import dashboard from '../views/dashboard.vue'
 import request from '../views/request.vue'
 import stud_dash from '../views/stud_dash.vue'

import students from '../views/students.vue'
import view_details from '../views/view_details.vue'
 

const routes = [
  
  { path: '/',
    name:"login", 
    component: login
  },
  {
    path: '/analytics',
    name: 'analytics',
    component: analytics
  },
  {
    path:'/dashboard',
    name:'dashboard',
    component:dashboard
    
  },
  {
    path:'/request',
    name:'request',
    component:request
    
  },
  
 
  {
    path:'/stud_dash',
    name:'stud_dash',
    component:stud_dash
    
  },
  {
    path:'/students',
    name:'students',
    component:students
    
  },
  {
    path:'/view_details',
    name:'view_details',
    component:view_details
    
  }
  

]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

export default router;