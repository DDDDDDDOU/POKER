
import React from 'react';
import {
    View,
    Text,
    AsyncStorage,
    ImageBackground,
    ActivityIndicator,
    FlatList,
    Image,
    StyleSheet,
    TouchableHighlight,
    Button
} from 'react-native';
import {SearchBar} from '../components/SearchBar';
import { SafeAreaView } from 'react-native-safe-area-context';
import {Home} from '../components/Home'
import {apiUrl} from '../urlconfig';
const styles = StyleSheet.create({
    footer:{
        flexDirection:"row",
        justifyContent: "center",
        alignItems: "center",
        backgroundColor:"rgba(255,255,255,0.6)",
        height:50
    },
    foottext:{
        height:50,
        lineHeight:50,
        fontSize:20,
        paddingRight: 50,
    },
    footbutton:{
        height:50,
        width:100,
        fontSize:30,
        backgroundColor:"rgba(255,0,0,0.7)"

    },
    container: {
        height:100,
        flexDirection:"row",
        justifyContent: "center",
        alignItems: "center",
        backgroundColor: "rgba(255,255,255,0)"
    },
    rrcontainer:{
        flex: 1,
        height:100,
        paddingRight:0,
        flexDirection:"row",
        justifyContent: "center",
        alignItems: "center",
        backgroundColor: "rgba(255,255,255,0)"
    },
    name: {
        fontSize: 18,
        marginBottom: 8,
        textAlign: 'center',
    },
    author: {
        fontSize:10,
        textAlign: 'center',
    },
    rightContainer: {

        flex: 1,
        paddingRight:10,
        backgroundColor: "rgba(255,255,255,0)"
    },
    image: {
        marginLeft:20,
        width: 53,
        height: 81
    },
    list: {
        paddingLeft:10,
        paddingRight:5,
        marginTop: 5,
        backgroundColor: 'rgba(255,255,255,0)',
    },
});

const GETBOOKS_URL=apiUrl+"/readOrder";
var lastorder="";

export class OrderScreen extends React.Component{
    constructor(props) {
        super(props);
        this.state ={
            books:[],
            showBooks:[],
            isLoading: true,
            userid:"",
            total:0,
            lastorder:"",
        }
    }

    componentDidMount(){
        this._navListener = this.props.navigation.addListener('didFocus', () => { this.fetchData(); });
        AsyncStorage.getItem('userid', (error, result)=> {
            if(error){
                console.log('读取失败');
            }else{
                console.log(result);
                if (result!=null) {
                    this.setState({
                        userid:result
                    })
                };
            }
        });
        const _retrieveData = async () => {
            try {
                const value = await AsyncStorage.getItem('@Bookstore:token');
                if (value !== null) {
                    // We have data!!
                    this.fetchData();
                }
            } catch (error) {
                // Error retrieving data
            }
        }
        _retrieveData();
    }
    componentWillUnmount() { this._navListener.remove(); }
    fetchData() {

        fetch(GETBOOKS_URL, {
            method: 'POST',

            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                "userid":this.state.userid,

            }),
        })
            .then((response) => response.json())
            .then((responseData) => {
                console.log(responseData)
                // 注意，这里使用了this关键字，为了保证this在调用时仍然指向当前组件，我们需要对其进行“绑定”操作

                this.setState({
                    isLoading:false,
                    books: responseData,
                });


            })
            .catch((error)=> {
                console.error(error);
            });
    }

    a

    navigateToDetail({item}){
        this.props.navigation.push("Detail",{detail:item});


        // var navigationOptions = ({ navigation }) => {
        //     const { params } = navigation.state;
        //     return{
        //         title:params ? params.name : '陌生人',
        //     }
        // };

    }

    renderBook=({ item })=>{
        if(item.orderid!=this.state.lastorder){
            this.state.lastorder=item.orderid;
            return(
                <View marginTop={5} marginBottom={5} style={{backgroundColor: "rgba(255,255,255,0.5)"}}>
                    <View marginTop={5} marginBottom={5} style={{backgroundColor: "rgba(255,255,255,0.5)"}}>
                        <Text >订单编号:{item.orderid}</Text>
                        <Text>购买时间:{item.buytime}</Text>
                    </View>
                    <TouchableHighlight  marginTop={5} style={{backgroundColor: "rgba(255,255,255,0)"}}>
                        <View style={styles.container}>
                            <Image
                                source={{uri: item.b['image']}}
                                style={styles.image}
                            />
                            <View style={styles.rightContainer}>
                                <Text style={styles.name}>{item.b['name']}</Text>
                                <Text style={styles.author}>{item.username}</Text>
                                {/*<Text style={styles.author}>{item.buytime}</Text>*/}
                            </View>
                            <View style={styles.rrcontainer}>
                                <Text>¥{item.b['price']}</Text>
                            </View>
                            <View style={styles.rrcontainer}>
                                <Text>数量:{item.num}</Text>
                            </View>
                        </View>
                    </TouchableHighlight>
                </View>
            )
        }
        else return (
            <View marginTop={5} marginBottom={5} style={{backgroundColor: "rgba(255,255,255,0.5)"}}>
                <TouchableHighlight  marginTop={5} style={{backgroundColor: "rgba(255,255,255,0)"}}>
                    <View style={styles.container}>
                        <Image
                            source={{uri: item.b['image']}}
                            style={styles.image}
                        />
                        <View style={styles.rightContainer}>
                            <Text style={styles.name}>{item.b['name']}</Text>
                            <Text style={styles.author}>{item.username}</Text>
                            <Text style={styles.author}>{item.buytime}</Text>
                        </View>
                        <View style={styles.rrcontainer}>
                            <Text>¥{item.b['price']}</Text>
                        </View>
                        <View style={styles.rrcontainer}>
                            <Text>数量:{item.num}</Text>
                        </View>
                    </View>
                </TouchableHighlight>
            </View>

        );
    }


    render(){
        if(this.state.isLoading){
            return(
                <View style={{flex: 1, padding: 20}}>
                    <ActivityIndicator/>
                </View>
            )
        }
        return (

            <SafeAreaView style={{ flex: 1}} >
                <ImageBackground style={{ flex: 1 }}
                                 source={require('../pic/bg2.jpg')} >
                    <FlatList
                        data={this.state.books}
                        renderItem={this.renderBook}
                        style={styles.list}
                        keyExtractor={item=>item.id}
                        ItemSeparatorComponent={ this._renderItemSeparatorComponent }
                    />
                    <View style={styles.footer}>
                        <Text style={styles.foottext}>购物车</Text>
                    </View>
                </ImageBackground>

            </SafeAreaView>


        );
    }
}
