
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

const GETBOOKS_URL=apiUrl+"/readCart";
const UPDATE_URL=apiUrl+"/updateCart";
const  BUY_URL=apiUrl+"/buy"
export class CartScreen extends React.Component{
    constructor(props) {
        super(props);
        this.state ={
            books:[],
            showBooks:[],
            isLoading: true,
            userid:"",
            total:0,
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

                // 注意，这里使用了this关键字，为了保证this在调用时仍然指向当前组件，我们需要对其进行“绑定”操作
                var to=0.00;
                for(var i=0;i<responseData.length;++i){

                    to+=parseFloat(responseData[i].price)*parseInt(responseData[i].num);
                    to=parseFloat(to.toFixed(2));

                }
                this.setState({
                    isLoading:false,
                    books: responseData,
                    total:to
                });


            })
            .catch((error)=> {
                console.error(error);
            });
    }
    updafetch(newb,bookid,num){
        console.log(bookid+":"+num);
        fetch(UPDATE_URL, {
            method: 'POST',

            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                "userid":this.state.userid,
                "bookid":bookid,
                "num":num
            }),
        }) .then(()=>{
            this.setState({
                books:newb
            })
        })
            .catch((error)=> {
                console.error(error);
            });
    }
    getText(data) {
        var arr=[];
        var list=this.state.books;
        for (var i = 0; i < list.length; i++) {
            if (list[i].name.indexOf(data) >= 0||
                list[i].type.indexOf(data) >= 0||
                list[i].author.indexOf(data) >= 0||list[i].description.indexOf(data) >= 0) {
                arr.push(list[i])
            }
        }
        this.setState({
            showBooks:arr
        })
    }
    addc(bookid,num){
        var newb=this.state.books;
        var newto=this.state.total;

        for(var i =0;i<newb.length;++i){
            if(newb[i].bookId==bookid){
                if(!(newb[i].num<=0&&num<0)) {
                    newb[i].num+=num;
                    newto+=parseFloat(newb[i].price);
                    newto=parseFloat(newto.toFixed(2));
                    this.setState({
                        total:newto
                    })
                    this.updafetch(newb,bookid,newb[i].num);
                }
                return;
            }

        }
        this.setState({
            books:newb
        })
    }

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
        return (
            <View marginTop={5} marginBottom={5} style={{backgroundColor: "rgba(255,255,255,0.5)"}}>
                <TouchableHighlight  marginTop={5} style={{backgroundColor: "rgba(255,255,255,0)"}}>
                    <View style={styles.container}>
                        <Image
                            source={{uri: item.image}}
                            style={styles.image}
                        />
                        <View style={styles.rightContainer}>
                            <Text style={styles.name}>{item.name}</Text>
                            <Text style={styles.author}>{item.author}</Text>
                        </View>
                        <View style={styles.rrcontainer}>
                            <Text>¥{item.price}</Text>
                        </View>
                        <View style={styles.rrcontainer}>
                            <Button   title="-" color={'gray'} onPress={()=>{this.addc(item.bookId,-1)}} />
                            <Text>{item.num}</Text>
                            <Button  title="+" color={'gray'} onPress={()=>{this.addc(item.bookId,1)}} />
                        </View>
                    </View>
                </TouchableHighlight>
            </View>

        );
    }

    buy=()=> {
        fetch(BUY_URL, {
            method: 'POST',

            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                "userid":this.state.userid,

            }),
        })
            .then(() => {

                // 注意，这里使用了this关键字，为了保证this在调用时仍然指向当前组件，我们需要对其进行“绑定”操作

                this.setState({
                    isLoading:false,
                    books: [],
                    total:0
                });
                alert("购买成功！")


            })
            .catch((error)=> {
                console.error(error);
            });
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
                        keyExtractor={item => item.bookId}
                        ItemSeparatorComponent={ this._renderItemSeparatorComponent }
                    />
                    <View style={styles.footer}>
                        <Text style={styles.foottext}>总价：{this.state.total}</Text>
                        <TouchableHighlight   style={{backgroundColor: "rgba(255,0,0,0.7)" , borderRadius:20,width:150 }} >
                            <Button style={styles.footbutton} title="下单" onPress={this.buy}/>
                        </TouchableHighlight>
                    </View>
                </ImageBackground>

            </SafeAreaView>


        );
    }
}
