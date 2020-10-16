package com.example.last.entity;

import com.fasterxml.jackson.annotation.JsonIdentityInfo;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.ObjectIdGenerators;
import lombok.Data;
import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;


@Data
@Entity
@Table(name = "cart")
@JsonIgnoreProperties(value = {"handler","hibernateLazyInitializer","fieldHandler"})
@JsonIdentityInfo(generator = ObjectIdGenerators.PropertyGenerator.class,property = "bookId")
public class Cart {
    public Cart(){

    }
    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    private int id;
    private int userid;
    private int  bookid;
    private int num;

    public int getuserid(){return this.userid;}
    public void setuserid(int userid){
        this.userid=userid;
    }
    public int getbookid(){return this.bookid;}
    public void setbookid(int bookid){
        this.bookid=bookid;
    }
    public  int getnum(){return this.num;}
    public void setnum(int num) {this.num=num;}


}
