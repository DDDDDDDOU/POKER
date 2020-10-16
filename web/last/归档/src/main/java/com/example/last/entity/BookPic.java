package com.example.last.entity;
import com.fasterxml.jackson.annotation.*;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.*;
@Document(collection = "book")
public class BookPic {
    @Id
    private int id;

    private String bookurl;

    public BookPic(int id, String bookurl) {
        this.id = id;
        this.bookurl = bookurl;
    }

    public String getBookurl() {
        return bookurl;
    }

    public void setBookurl(String bookurl) {
        this.bookurl = bookurl;
    }

}
