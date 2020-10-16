<template>
    <div>
    <div id="border">
        <div class="bookdetail">
            <div id="picdiv"><img v-bind:src="book['image']" id="pic"></div>
        </div>
        <div class="bookdetail">
            <div id="infodiv">

                <div class="infounit1">
                    <span class="Default">书名：</span>
                    <div><input class="inp1" v-if="isEditing1" v-bind:placeholder='this.newName' v-model="newName" @keyup.enter="ChangeName" /></div>
                    <div class="Name n1" v-if="!isEditing1" v-on:dblclick="ChangeName">
                        <span>《{{book["name"]}}》</span>
                    </div>
                </div>

                <div class="infounit2">
                    <span class="Default">价格：</span>
                    <div><input class="inp2" v-if="isEditing2" v-bind:placeholder="this.book['price']" v-model="newPrice" @keyup.enter="ChangePrice"/></div>
                    <div class="Name n2" v-if="!isEditing2" v-on:dblclick="ChangePrice">
                        <span>{{book["price"]}}</span>
                    </div>
                </div>

                <div class="infounit3">
                    <span class="Default">简介：</span>
                    <div><textarea  maxlength="100" class="inp3" v-if="isEditing3" v-bind:placeholder="this.book['description']" v-model="newComment" @keyup.enter="ChangeComment"/></div>
                    <div class="Name n3" v-if="!isEditing3" v-on:dblclick="ChangeComment">
                        <span>{{book["description"]}}</span>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <button id="add" v-on:click="add">加入购物车</button>
        <button id="save" v-on:click="savechange">保存修改</button>
    </div>
</template>

<script>
    import {addCart} from "@/services/bookService";
    import {updateBook} from "@/services/bookService";

    export default {
        data() {
            return {
                isEditing1: false,
                isEditing2: false,
                isEditing3: false,
                book:[],
                bookindex:'',
                currentbook: '',
                newName: "",
                newPrice: "",
                newComment:"",
                save:true
            }
        },
        name: "BookDetail",

        methods: {
            add(){
                this.savechange();
               addCart(sessionStorage.getItem('userid'),this.book['bookId'],this.callback);
            },
            savechange(){
                updateBook(this.book,this.afterchange);
            },
            afterchange(data){
                if(data){
                this.save=true;
                alert("OK!")}
            },
            init() {

                this.book = this.$route.query.book;
                this.newName=this.book["name"];
                this.save=true;
                console.log(this.book);
                // this.bookindex = this.$route.query.index;
                this.$emit("viewIn", this.book["name"]);


            },
            callback(data){
                if(data)
                alert("Done！");
            },
            ChangeName() {
                this.save=false;
                let name=this.newName;
                if(name[0]!='《') name="《"+name;
                if(name[name.length-1]!="》") name+="》";
                this.book["name"] = this.newName;
                this.isEditing1 = !this.isEditing1;
            },
            ChangePrice() {
                this.save=false;
                let P=this.newPrice;
                for(let i=0;i<P.length;++i){
                    if((P[i]>'9'||P[i]<'0')&&i!=P.length-1)
                    {alert("Please input number only!");
                        return;}
                    if(i==P.length-1&&P[i]!="¥"){
                        alert("Please end with a '¥'");
                        return;
                    }
                    else if(i==P.length-1&&P[i]!="¥") P+="¥";}
                this.book["price"] = P;
                this.isEditing2 = !this.isEditing2;
            },
            ChangeComment() {
                this.save=false;
                this.book["description"] = this.newComment;

                this.isEditing3 = !this.isEditing3;
            }
        },
        mounted() {
            this.init();
        },
        beforeDestroy() {
           // this.currentbook[3]=this.bookindex;

            this.$emit("viewOut");

        }
    }
</script>

<style scoped>
    #add{
        width: 40%;
        height: 40px;
        margin-left: 30%;
        margin-top: 20px;
        font-size: 20px;
        text-align: center;
        background: darkgray;
    }
    #save{
        width: 40%;
        height: 40px;
        margin-left: 30%;
        margin-top: 20px;
        font-size: 20px;
        text-align: center;
        background: darkgray;
    }
    #border {
        display: table;
        background: none;
        margin-left: auto;
        margin-right: auto;
    }

    .bookdetail {
        display: table-cell;
        vertical-align: top;
    }

    #picdiv {
        width: 500px;
        height: 400px;
        display: block;
        margin-top: 200px;
    }

    #infodiv {
        width: 600px;
        height: 400px;
        display: block;
        alignment: top;
        margin-top: 200px;
        text-align: center;
    }

    #pic {

        width: 100%;
        height: 400px;
        overflow: hidden;

    }

    .Name {
        width: 500px;
        cursor: text;
        height: 80px;
        text-align: center;
        margin-left: 50px;
    }
    .n1 {
        font-size: 50px;
    }
    .n2{
        font-size: 50px;
    }
    .n3{
        font-size: 20px;
    }


    .inp1{
        height: 80px;
        width: 600px;
        font-size: 50px;
        line-height: 80px;
        text-align: center;
    }
    .inp2{
        height: 80px;
        width: 600px;
        font-size: 50px;
        line-height: 80px;
        text-align: center;
    }
    .inp3{
        height: 80px;
        width: 600px;
        font-size: 20px;
        text-align: center;
        overflow: visible;
        resize: none;
        max-lines: 4;

    }
    .infounit1{
        width: 600px;
        height: 120px;
        text-align: left;
    }
    .infounit2{
        width: 600px;
        height: 120px;
        text-align: left;
    }
    .infounit3{
        width: 600px;
        height: 160px;
        text-align: left;
    }
    .Default{
        height: 40px;
        width: 450px;
        margin-left: 50px;
        font-size: 30px;
    }

</style>