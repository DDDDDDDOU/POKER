
import React from 'react';
import {Button, View,Text} from 'react-native';
import { createDrawerNavigator } from '@react-navigation/drawer';
import {Profile} from '../components/Profile';
import { createStackNavigator} from '@react-navigation/stack';
import {BookScreen} from './BookScreen';
import {BookListScreen} from "./BookListScreen"
import { SafeAreaProvider} from 'react-native-safe-area-context';
import {LoginScreen} from "./LoginScreen";
import {Home} from "../components/Home";

const Stack = createStackNavigator();
function BookListAndDetail(){
    return (
        <SafeAreaProvider>
        <Stack.Navigator>
            {/*<Stack.Screen name="Login" component={LoginScreen} options={{headerShown:false}} />*/}
            <Stack.Screen name="BookList" component={BookListScreen} options={{headerShown:false}}/>
            <Stack.Screen name="Login" component={LoginScreen} options={{headerShown:false}} />

            <Stack.Screen name="Detail" component={BookScreen} options={{headerShown:false}}/>

        </Stack.Navigator>
            </SafeAreaProvider>
    );
}
function MyCartScreen({ navigation }) {
    return (
        <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
            <Text>My Cart</Text>
        </View>
    );
}

function MyOrderScreen({navigation}) {
    return (
        <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
            <Text>My Order</Text>
        </View>
    );
}

function MyProfileScreen({navigation}) {
    return (
        <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
            <Profile navigation={navigation}/>
        </View>
    );
}

 // const Drawer = createDrawerNavigator(
//{
//     Books: {
//         screen: {BookListAndDetail}
//     },
//     MyCart: {
//         screen: {MyCartScreen}
//     },
//     MyOrder: {
//         screen: {MyOrderScreen}
//     },
// }, {
//     order: ['Books', 'MyCart', 'MyOrder'],//routeNames数组，用于定义抽屉项目的顺序。
//     //initialRouteName: '',//初始路由的routeName。
//     drawerLockMode: 'locked-open',//设置是否响应手势
//     //'unlocked'   可以通过手势和代码 打开关闭抽屉
//     //'locked-closed' 抽屉关闭状态  不能通过手势打开  只能通过代码实现
//     //'locked-open'  抽屉打开状态  不能通过手势关闭  只能通过代码实现
//
//
//     drawerWidth: 250, //抽屉的宽度或返回的功能。
//     drawerPosition: 'left', //选项是left或right。默认是left位置。
//     useNativeAnimations: true, //启用原生动画。默认是true。
//     drawerBackgroundColor: 'pink', //使用抽屉背景获取某种颜色。默认是white。
//
//     //用于呈现抽屉内容的组件，例如导航项。收到navigation抽屉的道具。默认为DrawerItems
//     //用于自定义
//     //contentComponent: '',
//
//
//     //配置抽屉内容  items相关
//     contentOptions: {
//         // items: [OtherScreen],//可以修改或覆盖路由数组  不知道干嘛用的
//         // activeItemKey: 'AppInfo', //识别活动路线的关键  也不知道干嘛用的
//
//         activeTintColor: 'white', //活动标签的标签和图标颜色
//         activeBackgroundColor: 'blue', //活动标签的背景颜色
//         inactiveTintColor: 'black', //非活动标签的标签和图标颜色
//         inactiveBackgroundColor: 'red', //非活动标签的背景颜色
//
//         // //按下项目时要调用的函数 不知道是否使用错误 一直没反应
//         //github上面有答案 在自定义视图的时候 会有用
//         // onItemPress(route) {
//         //     console.log('onItemPress'+route);
//         // },
//
//
//         // itemsContainerStyle: '', //内容部分的样式对象
//         // itemStyle: '', //单个项目的样式对象，可以包含图标和 / 或标签
//         // labelStyle: '', //Text当标签是字符串时，样式对象在内容部分内覆盖样式
//         // activeLabelStyle: '', //Text当标签是字符串（与之合并labelStyle）时，样式对象覆盖活动标签的样式
//         // inactiveLabelStyle: '', //Text当标签是字符串（与之合并labelStyle）时，样式对象覆盖非活动标签的样式
//         // iconContainerStyle: '', //样式对象以覆盖View图标容器样式。
//     }
//
// }
// )

export function HomeScreen(){
    return (

            // <Drawer.Navigator backBehavior={'order'} drawerStyle={{
            //     backgroundColor: '#c6cbef',
            //     width: 350,
            //     paddingTop:100,
            //     fontSize:30,
            //
            //
            // }} >
            //     <Drawer.Screen name="书籍" component={BookListAndDetail}/>
            //     <Drawer.Screen name="购物车" component={MyCartScreen} />
            //     <Drawer.Screen name="我的订单" component={MyOrderScreen} />
            //     <Drawer.Screen name="注销" component={MyProfileScreen} />
            // </Drawer.Navigator>
        <BookListAndDetail />
        // <Drawer>
        //
        // </Drawer>

    );
}



    // export function HomeScreen() {
    //     return (
    //         <AppContainer></AppContainer>
    //     )
    // }