
import React from 'react';
import {View, Text, Image, StyleSheet, Button, Alert, Dimensions, AsyncStorage} from 'react-native';
import {BookListScreen} from "./BookListScreen";
// import {isDetail} from "../components/Detail";
import {AuthContext} from "../context";
let {width,height} = Dimensions.get('window');
import {apiUrl} from '../urlconfig';

let addtocartURL=apiUrl+"/addCart";

export class BookScreen extends React.Component {
    // static navigationOptions ={
    //     headerShwon:!this.props.navigation.state.params.headerShown,
    // };


    constructor(props) {

        super(props);

        this.state ={
            book:"",
            userid:""
        }

    }

    componentDidMount=()=> {
        let detail=this.props.route.params.detail;
        AsyncStorage.getItem('userid', (error, result)=> {
            if(error){
                console.log('读取失败');
            }else{
                console.log(result);
                if (result!=null) {
                    this.setState({
                        book:detail,
                        userid:result
                    })
                };
            }
        })


    }
    addtocart=()=>{



        fetch(addtocartURL, {
            method: 'POST',

            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                "bookid": this.state.book.bookId,
                "userid": this.state.userid
            }),
        })
            .then((response) => response.json())
            .then((responseData) => {
                // 注意，这里使用了this关键字，为了保证this在调用时仍然指向当前组件，我们需要对其进行“绑定”操作
                // this.setState({
                //     isLoading:false,
                //     books: responseData,
                //     showBooks:responseData
                // });
                alert("OK!");

            })
            .catch((error)=> {
                console.error(error);
            });
    }

    render(){
        // const{ Detail } = React.useContext(AuthContext);
        // console.log(this.props.route.params.detail);
        let detail=this.props.route.params.detail;
        return (
            <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>

                    {/*<View style={styles.contain}>*/}
                    {/*    <View style={styles.myButton}>*/}
                    {/*        <Button style={{marginTop:20}} title="登录"  />*/}
                    {/*    </View>*/}
                    {/*</View>*/}


                            <Image
                                source={{uri: detail.image}}
                                style={styles.image}
                            />


                            <View >
                                <Text style={styles.name}>{detail.name}</Text>
                            </View>
                            <View >
                                <Text >作者：{detail.author}</Text>
                                <Text >ISBD：{detail.isbn}</Text>
                                <Text >类型：{detail.type}</Text>
                                <Text>单价：¥{detail.price}</Text>
                                <Text>库存：{detail.inventory}</Text>
                            </View>
                            <View>
                                <Text style={styles.description}>&emsp;&emsp;{detail.description}</Text>
                            </View>






                {/*<View style={styles.clickButtonStyle} >*/}
                {/*    <Button  title="返回" color={'green'} onPress={this.props.navigation.goBack} />*/}
                {/*</View>*/}

                <View style={styles.bottom}>
                    <Button  title="返回" color={'green'} onPress={this.props.navigation.goBack} />
                    <Button style={styles.bottombutton} title="加入购物车" color={"orange"} onPress={this.addtocart} />
                </View>


            </View>
        );
    }
}

const styles = StyleSheet.create({
    name:{
        marginTop:30,
        fontSize:20
    },
    clickButtonStyle: {
        marginLeft:-250,
        width:70,
        height: 70,
        backgroundColor: '#E6E6FA',
        borderRadius: 150,
        borderWidth: 1,
        borderColor: '#7FFF00',
        marginTop:50,
        paddingTop:15


    },
    bottom:{
        width:width,
        height:60
    },

    bottombutton:{
        height:30,
        width:0.4*width,
        backgroundColor:'rgba(222,69,0,0.8)'
    },
        image: {
        marginTop:20,
        width: 182,
        height: 245
    },
    description:{
        paddingLeft:50,
        paddingRight:55,
        marginTop:30,
    }
});