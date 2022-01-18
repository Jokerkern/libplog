import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
import About from '../views/About.vue'
import Setting from '../views/Setting.vue'
import Logorm from '../views/Logorm.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Aboud',
    component:About,
    meta: {
      keepAlive: true
    }
  },
  {
    path: '/About',
    name: 'About',
    component: About,
    meta: {
      keepAlive: true
    }
  },
  {
    path: '/Home',
    name: 'Home',
    component: Home,
    meta: {
      keepAlive: true
    }
  },
 

  {
    path: '/Logorm',
    name: 'Logorm',
    component: Logorm,
    meta: {
      keepAlive: true
    }
  },
   {
    path: '/Setting',
    name: 'Setting',
    component: Setting,
  },
  ]

const router = new VueRouter({
  base: process.env.BASE_URL,
  routes
})

export default router
