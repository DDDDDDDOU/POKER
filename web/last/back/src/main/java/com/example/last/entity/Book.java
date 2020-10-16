package com.example.last.entity;

import com.fasterxml.jackson.annotation.JsonIdentityInfo;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.ObjectIdGenerators;
import lombok.Data;

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
    private String image;
    public void setname(String n){this.name=n;}
    public void setprice(String p){this.price=p;}
    public void setdescription(String d){this.description=d;}



}
