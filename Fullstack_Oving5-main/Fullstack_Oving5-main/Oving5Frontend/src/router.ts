import { createRouter, createWebHistory } from 'vue-router'
import Login from './components/Login.vue'
import Calculator from './components/Calculator.vue'

// Define the routes for the application
// Each route should map a URL path to a component
const routes = [
  { path: '/', component: Login }, // Default route
  { path: '/calculator', component: Calculator } // About page route
]

// Create the router instance and pass the `routes` option
// This will create a router instance that we can use in our main.ts file
const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router