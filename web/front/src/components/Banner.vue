<template>
    <div id="banner">
<!--        <swiper-slide-->
        <img class="slide" v-bind:src=burl alt="123" />
    </div>
</template>

<script>


    export default {
        props:["banner1"],
        data(){
            return{
                intervalID:"",
                index:0,
                banner: '',
                burl:'/gugong.jpg'

            }
        },
        name: "Bannner",
        methods:{
            ticked(){
                this.index=(this.index+1)%3;
                this.burl=this.banner[this.index];
                // alert(this.index);
            }
        },
        mounted(){
            this.banner=this.banner1;
            this.intervalID = setInterval(this.ticked,2000);
        },
        destroyed(){
            clearInterval(this.intervalID);//清除计时器
        },
    }
</script>

