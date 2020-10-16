<template>
    <div>
    <Dao/>
    <div id="login_div">
        <div class="login_form">
            <input type="text"  class="qxs-ic_user qxs-icon"  placeholder="用户名" v-model="userName">
            <input type="text"  class="qxs-ic_password qxs-icon"  placeholder="密码" v-model="password">
            <!--<button class="login_btn el-button el-button&#45;&#45;primary is-round" type="primary" round>登录</button>-->
            <el-button class="login_btn"  v-on:click="login" type="primary" round :loading="isBtnLoading">登录</el-button>
        </div>
    </div>
    </div>
</template>



<script>
    import Dao from '../components/Dao.vue';
    import * as userService from "../services/userService";


    import {message} from 'antd';



    //  import { userLogin } from '../../api/api';

    export default {
        data() {
            return {
                userName: '',
                password: '',
                isBtnLoading: false
            }
        },
        created () {
            // if(JSON.parse( localStorage.getItem('user')) && JSON.parse( localStorage.getItem('user')).userName){
            //     this.userName = JSON.parse( localStorage.getItem('user')).userName;
            //     this.password = JSON.parse( localStorage.getItem('user')).password;
            // }
        },
        computed: {
            btnText() {
                if (this.isBtnLoading) return '登录中...';
                return '登录';
            }
        },
        destroyed(){

        },
        methods: {
            login() {
                if (!this.userName) {
                    message.error('请输入用户名');
                    return;
                }
                if (!this.password) {
                    message.error('请输入密码');
                    return;
                }
                console.log("username:"+this.userName);
                console.log("password:"+this.password);
                if(this.username!='' &&this.password!=''){
                    console.log("username and password assigned");
                    let data={
                        "username":'',
                        "password":'',
                        "remember":false
                    };
                    data["username"]=this.userName;
                    data["password"]=this.password;
                    console.log(data);
                    userService.login(data);
                    let da=sessionStorage.getItem("user");
                    if(da[da.indexOf("userType")+10]=='0') this.$root.superuser=true;
                    this.$root.logged=false;


                }

            }
        },
        components:{
            Dao
        }
    }
</script>
<style>
    .login_form {
        padding-top: 300px;
        padding-left: 20%;
        width: 60%;
        height: 200px;
    }
    .qxs-ic_user {
        background: url('../pic/usr.png') no-repeat;
        background-size: 13px 15px;
        background-position: 3%;
    }
    .qxs-ic_password {
        background: url('../pic/usrp.png') no-repeat;
        background-size: 13px 15px;
        background-position: 3%;
        margin-bottom: 20px;
    }

    .login_btn {
        width: 100%;
        font-size: 16px;
        background: gray;
        filter: brightness(1.4);
    }
</style>