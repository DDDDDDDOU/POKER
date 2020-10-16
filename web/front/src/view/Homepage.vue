<template>
    <div id="app">
        <Dao/>
        <div id="level1"  v-if="Mode==0">
            <div id="level2.1"></div>
            <div id="level2.2">
                <div id="banner">
                    <Banner v-bind:banner1="Ban"/>
                </div>
                <div id="search_div">
                    <input id="search" type="text" v-bind:placeholder=books[0][0] v-model="inputV" />
                    <button id="search_button" v-on:click="button_clicked()">搜索</button>
                </div>
                <Books :book="books" />
            </div>
            <div id="level2.3"></div>
        </div>
<!--        <transition v-on:after-enter="changeMode">-->
<!--        <router-view v-on:viewIn="changeMode"></router-view>-->
<!--        </transition>-->
        <router-view v-on:viewIn="changeMode" v-on:viewOut="homeMode"></router-view>
    </div>
</template>

<script>
    import Dao from '../components/Dao.vue'
    import Banner from '../components/Banner'
    import Books from "@/components/Books";
    import {getBooks} from "@/services/bookService";

    export default {
        inject:['reload'],//刷新
        data() {
            return {
                inputV:"",
                bookdetail:'',
                Mode:0,
                Ban: ['/gugong.jpg', '/qingyunian.jpg', '/shaoniandeni.jpg'],
                body_img: 'url(' + require('../pic/beijing.png') + ')',
                books:[],
                lastbooks:[],
                bookli:[]
            }
        },
        name: "Homepage",
        watch:{
            inputV(){
                this.search();
            },

        },
        methods: {
            changeMode:function (mode) {
                this.Mode=mode;
            },
            homeMode(){


                this.Mode=0;
            },
            setBodyBg() {
                document.body.style.background = this.body_img;
            },
            button_clicked(){
                 this.Mode++;
                if(this.inputV==''){
                    getBooks({"search":null}, this.callback);

                }
                else{
                    this.lastbooks = this.books;
                    this.search();
                }
            },
            search(){

                var newbooks = new Array();
                if(this.inputV==''){
                    getBooks({"search":null}, this.callback);

                }
                for(let x in this.books){
                    if(this.books[x]["name"].indexOf(this.inputV)!=-1)
                    {
                        newbooks.push(this.books[x]);
                    }
                }
                this.books = newbooks;

            },
            callback(data){
                this.books=data;
                console.log(data);
               // alert(this.books);

                console.log(this.books);
            }
        },
        mounted() {
            console.log("mounted");
            this.Mode=this.$route.params.id;
            this.setBodyBg();
            //alert("a");
            getBooks({"search":null}, this.callback);
        },

        components: {
            Dao,
            Banner,
            Books
        }
    }
</script>

<style scoped>

</style>