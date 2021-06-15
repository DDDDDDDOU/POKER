
import React,{useState}from 'react';
import {
    AsyncStorage,
    StyleSheet,
    View,
    Text,
    TextInput,
    Image,
    Dimensions,
    Button,
    Alert, ImageBackground
} from 'react-native';
import {AuthContext} from "../context";
import {apiUrl} from "../urlconfig";

// 获取屏幕的宽和高
let {width,height} = Dimensions.get('window');
const LOGIN_URL=apiUrl+"/login";
var isSuccess ;
function fetchData({name,password,signIn,navigation}) {
    fetch(LOGIN_URL,{
        method:'POST',
        credentials: 'include',
        headers: {
            'Content-Type': 'application/json',
        },
        body:JSON.stringify({
            "username":name,
            "password":password,
        }),
    })
        .then((response) => {
            // let cookie=response._bodyBlob._data.blobId;
            // console.log("cookie in login screen:"+JSON.stringify(response));
            let _storeData = async () => {
                try {
                    await AsyncStorage.setItem("@Bookstore:token",'exist');
                } catch (error) {
                    // Error saving data
                }
            };
            _storeData();
            return response.json();
        })
        .then((responseData) => {
            //var that=fetchData.bind(this);
            console.log(responseData.data);
            isSuccess=(responseData.status==0?true:false);
            if(isSuccess){
               // navigation.push("Home");
                signIn();
                var user=responseData.data;

               AsyncStorage.setItem("userid",user.userId.toString());
                navigation.navigate("Home");
              //  that.navigatetoBookList();
               // this.naviga();
            }else{
                Alert.alert("用户名或密码错误！");
            }
        })
        .catch((error)=>{
            console.error(error);
        });
}
function login() {
    Alert.alert("注册不了哦亲！")
}
function navigatetoBookList() {
    this.props.navigation.push("BookList")
}

export function LoginScreen({navigation}){
    const [name, setName] = useState('');
    const [password,setPassword]=useState('');
    const { signIn } = React.useContext(AuthContext);
   // const {navigate} = this.props.navigation;
    return (
        <ImageBackground style={{ flex: 1 }}
                         source={require('../pic/bg1.jpg')}>
            <View style={{ flex: 1}}>
                <View style={styles.container}>
                    <Text style={styles.titleStyle}>Login</Text>
                    {/*账号和密码*/}
                    <TextInput
                        style={styles.textInputStyle}
                        onChangeText={text => setName(text)}
                        value={name}
                        placeholder={'请输入用户名'}
                        autoCapitalize="none"


                    />

                    <TextInput
                        style={styles.textInputStyle}
                        placeholder='请输入密码'
                        onChangeText={text => setPassword(text)}
                        value={password}
                        password={true}
                        secureTextEntry={true}
                        autoCapitalize="none"

                    />

                    {/*登录*/}
                    <Button style={styles.loginBtnStyle} title="登录" onPress={() => {
                        fetchData({name,password,signIn,navigation});
                    }}  color={'black'} fontsize={20} >
                        {/*<text style={styles.titleStyle}>登陆</text>*/}

                    </Button>
                    <Button style={styles.loginBtnStyle} title="注册" onPress={login}
                    color={'black'} fontsize={20} >
                        {/*<text style={styles.titleStyle}>登陆</text>*/}

                    </Button>

                    {/*设置*/}
                    {/*<View style={styles.settingStyle}>*/}
                    {/*    <Text>忘记密码</Text>*/}
                    {/*    <Text>注册</Text>*/}
                    {/*</View>*/}

                </View>
            </View>
        </ImageBackground>

        );
}
const styles = StyleSheet.create({
    container: {
        flex: 1,
        // 侧轴的对齐方式
        justifyContent: "center",
        alignItems:'center',
    },
    textInputStyle: {
        width:width*0.9,
        height:40,

        backgroundColor:'rgba(255,255,255,0.5)',
        textAlign:'center',
        marginBottom:5,
    },
    loginBtnStyle: {
        width: width*0.9,
        height: 50,
        marginTop:40,
        marginBottom: 20,
        borderRadius:10,
        fontSize:40
    },
    settingStyle: {
        width: width*0.85,
        height: 40,
        flexDirection:'row',
        justifyContent:'space-between',
        alignItems:'center',
    },
    titleStyle: {
        fontSize:40,
        alignItems:'center',
        paddingBottom:10
    },

});