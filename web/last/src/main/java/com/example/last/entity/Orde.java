package com.example.last.entity;

import com.fasterxml.jackson.annotation.JsonIdentityInfo;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.ObjectIdGenerators;
import lombok.Data;
import org.apache.catalina.User;
import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;
import java.util.Date;


@Data
@Entity
@Table(name ="orde")
@JsonIgnoreProperties(value = {"handler","hibernateLazyInitializer","fieldHandler"})
//@JsonIdentityInfo(generator = ObjectIdGenerators.PropertyGenerator.class,property = "bookId")

public class Orde {
    public Orde(){

    }
    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    private int id;
    private int userid;
    private int  bookid;
    private String buytime;
    private int num;
    private String username;
    private String orderid;

    public void setuserid(int userid){
        this.userid=userid;
    }
    public void setbookid(int bookid){
        this.bookid=bookid;
    }
    public void setnum(int num) {this.num=num;}
    public void setBuytime(String buytime){this.buytime=buytime;}
    public void setUsername(String username) {this.username=username;}
    public void setorderid(String orderid){this.orderid=orderid;}



    @Transient
    private Book b;
    public void setb(Book b) {
        this.b=new Book();
        this.b.setPic(b.getImage());
        this.b.setInventory(b.getInventory());
        this.b.setnum(b.getNum());
        this.b.setdescription(b.getDescription());
        this.b.setprice(b.getPrice());
        this.b.setAuthor(b.getAuthor());
        this.b.setBookId(b.getBookId());
        this.b.setIsbn(b.getIsbn());
        this.b.setname(b.getName());
    }
    @Transient
    private UserAuth u;
    public void setu(UserAuth u){
        this.u=new UserAuth();
        this.u.setUsername(u.getUsername());
        this.u.setUserId(u.getUserId());
        this.u.setCost(u.getCost());
        this.u.setNum(u.getNum());
    }
    public UserAuth getu(){return this.u;}
}
