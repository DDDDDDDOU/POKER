//import config from 'config';
import {postRequest, postRequest_v2} from "../ajax/ajax.js";


export const getBooks = (data, callback) => {
    const url = `http://localhost:8080/getBooks`;
    console.log(url);
    postRequest(url, data, callback);
};

export const getBook = (id, callback) => {
    const data = {id: id};
    const url = `http://localhost:8080/getBook`;
    postRequest_v2(url, data, callback);

};
export const addCart = (uid,bid,callback)=>{

    const data  = {userid:uid,bookid:bid};
    const url = 'http://localhost:8080/addCart';
    postRequest(url,data,callback);
}
export const readCart = (uid,callback)=>{
    const data  = {userid:uid};
    const url = 'http://localhost:8080/readCart';
    postRequest(url,data,callback);
}
export const updateBook = (data,callback)=>{
    // const data  = {userid:uid};
    const url = 'http://localhost:8080/updateBook';
    postRequest(url,data,callback);
}