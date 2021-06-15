
import React from 'react';
import {View,Text,AsyncStorage,ImageBackground,ActivityIndicator, FlatList, Image,StyleSheet,TouchableHighlight} from 'react-native';
import {SearchBar} from '../components/SearchBar';
import { SafeAreaView } from 'react-native-safe-area-context';
import {Home} from '../components/Home'
import {apiUrl} from '../urlconfig';
//import {Home} from '../components/Home'
const styles = StyleSheet.create({
    container: {
        flex: 1,
        height:100,
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

const GETBOOKS_URL=apiUrl+"/getBooks";
export class BookListScreen extends React.Component{
    constructor(props) {
        super(props);
        this.state ={
            books:[],
            showBooks:[],
            isLoading: true,
            userid:""
        }
    }

    componentDidMount(){
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
    fetchData() {
        fetch(GETBOOKS_URL, {
            method: 'POST',

            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                "search": 'null',
            }),
        })
            .then((response) => response.json())
            .then((responseData) => {
                // 注意，这里使用了this关键字，为了保证this在调用时仍然指向当前组件，我们需要对其进行“绑定”操作
                this.setState({
                    isLoading:false,
                    books: responseData,
                    showBooks:responseData
                });
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
                <TouchableHighlight onPress={()=>{this.navigateToDetail({item});}} marginTop={5} style={{backgroundColor: "rgba(255,255,255,0)"}}>
                    <View style={styles.container}>
                        <Image
                            source={{uri: item.image}}
                            style={styles.image}
                        />
                        <View style={styles.rightContainer}>
                            <Text style={styles.name}>{item.name}</Text>
                            <Text style={styles.author}>{item.author}</Text>
                        </View>
                        <View style={styles.container}>
                            <Text>¥{item.price}</Text>
                        </View>
                    </View>
                </TouchableHighlight>
        </View>

        );
    }
    cancel(){
        this.setState({
            showBooks:this.state.books
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
                        <SearchBar searchBooks={(data) => this.getText(data)} cancelSearching={()=>this.cancel()}/>
                        <FlatList
                            data={this.state.showBooks}
                            renderItem={this.renderBook}
                            style={styles.list}
                            keyExtractor={item => item.bookId}
                            ItemSeparatorComponent={ this._renderItemSeparatorComponent }
                        />
                    </ImageBackground>

                </SafeAreaView>


        );
    }
}
