<template>
    <div>
        <Dao/>
        <Books :book="books" />
    </div>

</template>

<script>
    import {readCart} from "@/services/bookService";
    import Books from "@/components/Books";
    import Dao from "@/components/Dao";

    export default {
        name: "Cart",
        data(){
          return {
              books:[]
          }
        },
        methods:{
            callback(data){
                this.books=data;
                console.log(data);
                // alert(this.books);

                console.log(this.books);
            },

        },
        mounted(){
            console.log("readCart:");
            readCart(sessionStorage.getItem("userid"),this.callback);
            console.log(this.books);
        },
        components:{
            Books,
            Dao
        }
    }
</script>

<style scoped>

</style>