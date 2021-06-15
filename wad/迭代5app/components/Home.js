 import {createBottomTabNavigator} from "react-navigation-tabs";
import {LoginScreen} from "../screens/LoginScreen";
// import Ionicons from "react-native-vector-icons/Ionicons";
 import {createAppContainer} from "react-navigation";
 // import React from "react";
//import {HomeScreen} from "../screens/HomeScreen";

//
// const TabNavigator = createBottomTabNavigator(
//     {
//         Home:HomeScreen,
//         Login:LoginScreen
//     },
//     {
//         defaultNavigationOptions:({navigation,screenProps})=>({
//             tabBarIcon:({focused,horizontal,tintColor})=>{
//                 const {routeName} = navigation.state;
//                 let iconName;
//                 if(routeName=='Home'){
//                     iconName='ios-home'
//                 }else if(routeName=='Login'){
//                     iconName='ios-Login'
//                 }
//
//                 return <Ionicons name={iconName} size={25} color={tintColor} />;
//             },
//         }),
//         tabBarOptions:{
//             activeTintColor:"#409EFF",
//             inactiveTintColor:"#909399",
//         },
//
//
//
//
//     });
//
//
// const AppContainer= createAppContainer(BoNavigator);
// export function Home() {
//     return(<AppContainer/>);
// }



import React from 'react'


 function MyProfileScreen( ){
     return (
         <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
             <Profile />
         </View>
     );
 }
import Ionicons from 'react-native-vector-icons/Ionicons'
 import { createStackNavigator } from 'react-navigation-stack';
 import {View} from "react-native";
 import {Profile} from "./Profile";

 import {HomeScreen} from "../screens/HomeScreen";
 import {CartScreen} from "../screens/CartScreen";
 import {OrderScreen} from "../screens/OrderScreen";

const BottomNavigator = createBottomTabNavigator(
    {
        Home: {
            screen: HomeScreen,
            navigationOptions: {
                title: "首页",
                tabBarIcon:({ focused, horizontal, tintColor })=>{
                    return <Ionicons name={'ios-home'} size={25} style={{color:tintColor}}/>
                }
            }
        },
        Cart:{
            screen: CartScreen,
            navigationOptions: {
                title: "购物车",
                tabBarIcon:({ focused, horizontal, tintColor })=>{
                    return <Ionicons name={'ios-cart'} size={25} style={{color:tintColor}}/>
                }
            }
        },
        setting: {
            screen: OrderScreen,
            navigationOptions: {
                title: "订单",
                tabBarIcon:({ focused, horizontal, tintColor })=>{
                    return <Ionicons name={'ios-cog'} size={25} style={{color:tintColor}}/>
                }
            }
        },

    },
    {
        tabBarOptions:{
            activeTintColor:"red"
        }
    }
)

const Appcontainer= createAppContainer(BottomNavigator)
export class Home extends React.Component{
    render() {
        return(
            <Appcontainer>

            </Appcontainer>
        );
    }


}