package com.example.last.entity;

import com.fasterxml.jackson.annotation.*;
import com.example.last.entity.BookPic;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.ObjectIdGenerators;
import lombok.Data;
import java.util.ArrayList;
import java.util.List;

import javax.persistence.*;


@Data
@Entity
@Table(name = "book")
@JsonIgnoreProperties(value = {"handler","hibernateLazyInitializer","fieldHandler"})
@JsonIdentityInfo(generator = ObjectIdGenerators.PropertyGenerator.class,property = "bookId")
public class Book {

    @Id
    @Column(name = "id")
    private int bookId;

    private String isbn;
    private String name;
    private String type;
    private String author;
    private String price;
    private String description;
    private Integer inventory;
    private Integer total;
    //private String image;



    public void setname(String n){this.name=n;}
    public void setprice(String p){this.price=p;}
    public void setdescription(String d){this.description=d;}


    @Transient
    private String image;
    public String getImage(){
        return this.image;
    }
    public  void setPic(String bookPic){
        this.image = bookPic;
    }

    @Transient
    private  int num;
    public void setnum (int num){this.num=num;}

    @Transient
    private  Integer sale;
    public void setsale(){this.sale=this.total-this.inventory;}

}
