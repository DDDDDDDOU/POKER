import Vue from 'vue'
import VueRouter from 'vue-router'
import Homepage from "@/view/Homepage";
import Login from "./view/Login";
import BookDetail from "@/components/BookDetail";
import Cart from"./view/Cart"
// import BookDetail from "@/components/BookDetail";
// import Books from "@/components/Books";

Vue.use(VueRouter);
const routes = [
    {
        path:"/home",
        component: Homepage,
        children:[
            {
                path: "bookdetail",
                component: BookDetail,
            },

        ]
    },
    {
        path:"/home/:id",
        component: Homepage,

    },
    {
        path:"/Cart",
        component: Cart
    },
    {
        path: "/Login/:id",
        component: Login
    },
    {
        path:"/Login",
        component: Login
    },
    {
        path:"/home/bookdetail",
        component: BookDetail,
    },

    {
        path: '/*',
        redirect: '/home/0'
    }
]

var router =  new VueRouter({
    routes,
    mode:"history"
})
router.beforeEach((to, from, next) => {
    console.log(1);
    if(sessionStorage.getItem("user")!=null) next();
    else if(to.path=="/Login") {next()}
    else{
        next("/Login");
    }

});
export default router;