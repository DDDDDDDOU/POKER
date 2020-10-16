<template>
    <nav>
        <ul class="level">
            <li>
                <router-link to="/home/0">{{list1[0]}}</router-link>
            </li>
            <li>
                {{list1[1]}}
                <ul class="two">
                    <li><router-link to="/home/1">{{list2[1][0]}}</router-link></li>
                    <li> <router-link to="/home/2">{{list2[1][1]}}</router-link></li>
                    <li><router-link to="/home/3">{{list2[1][2]}}</router-link></li>
                </ul>
            </li>
            <li>
                <router-link to="/favor">{{list1[2]}}</router-link>
            </li>
            <li>
                {{list1[3]}}
                <ul class="two">
                    <li><router-link to="/cart">{{list2[3][0]}}</router-link></li>
                    <li><router-link to="/cart">{{list2[3][1]}}</router-link></li>
                </ul>
            </li>
            <li>
                {{list1[4]}}
                <ul class="two">
                    <li><router-link to="/Login/1">{{list2[4][0]}}</router-link></li>
                    <li><router-link to="/Login/2">{{list2[4][1]}}</router-link></li>
                    <li><router-link to="/Login/3">{{list2[4][2]}}</router-link></li>
                </ul>
            </li>
            <li>
                {{list1[5]}}
                <ul class="two">
                    <router-link to="/search/1"><li>{{list2[5][0]}}</li></router-link>
                    <router-link to="/search/2"><li>{{list2[5][1]}}</li></router-link>
                    <router-link to="/search/3"><li>{{list2[5][2]}}</li></router-link>
                </ul>
            </li>
        </ul>
    </nav>
</template>

<script>
    export default {
        data(){
            return {
                 list1 : ["首页", "全部书籍", "我的收藏", "购物车", "登陆/注册", "查找书籍"],
                 list2 : [[], ["最新上市", "最热书选", "综合排列"], [], ["查看购物车", "结算"], ["用户登陆", "注册新账号", "管理员登陆"], ["普通搜索", "高级搜索", "缺书报告"]]
            }
        },
        name: "Dao"
    }
</script>

