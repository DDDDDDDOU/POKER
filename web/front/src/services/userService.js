
import {postRequest} from "../ajax/ajax.js";
import {history} from '../ajax/history';
import {message} from 'antd';



export const login = (data) => {
    const url = `http://localhost:8080/login`;
    const callback = (data) => {
        if(data.status >= 0) {
            let d = JSON.stringify(data.data);

            sessionStorage.setItem('user', d.data);
            sessionStorage.setItem('userid',data.data['userId']);

           // let v=Object.values(d);
            //console.log(d);
            //console.log(d[d.indexOf("userType")+10]);
            //sessionStorage.setItem('userType',d["userType"]);
          //  console.log(data);
            //console.log(d["userType"]);
           // this.$root.superuser=!d["userType"];
            //console.log(this.$root.superuser);
           // this.$root.logged=true;
            history.push("/");
            message.success(data.msg);
        }
        else{
            message.error(data.msg);
        }
    };
    postRequest(url, data, callback);
};

export const logout = () => {
    const url = `http://localhost:8080/logout`;

    const callback = (data) => {
        if(data.status >= 0) {
            sessionStorage.removeItem("user");
            sessionStorage.removeItem("userid");
            history.push("/login");
            message.success(data.msg);
            console.log(data.user_type)
        }
        else{

            message.error(data.msg);
        }
    };
    postRequest(url, {}, callback);
};

export const checkSession = (callback) => {
    const url = `http://localhost:8080/checkssion`;
    postRequest(url, {}, callback);
};

