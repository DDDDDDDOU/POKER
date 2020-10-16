<template>
<div id="list">
    <li class="book_cell" v-for="(item) in books" :key="item">
        <div class="book_cell_div" v-on:click="cl(item)" >
            <router-link :to="{path:'/home/bookdetail',query:{book:item}}">
                <img class="pic" v-bind:src="item['image']" />
                <p class="book_cell_par">
                    {{item["name"]}}
                    {{item["price"]}}
                </p>
            </router-link>
        </div>
    </li>
</div>
</template>

<script>
    export default {
        name: "Books",
        props :['book'],
        methods:{
            cl(d){
                console.log(d["name"]);
            }
        },
        data() {
            return {
                books: [],
            }
        },
        watch:{
            book(){
                this.books = this.book;
    }
        },
        mounted(){
            this.books = this.book;
            console.log("receive!");
            console.log(this.books);
        }
    }
</script>

<style scoped>

</style>