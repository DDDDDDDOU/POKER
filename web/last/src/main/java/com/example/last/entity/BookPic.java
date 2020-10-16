package com.example.last.entity;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import javax.persistence.Column;
import javax.persistence.Entity;


@Document(collection = "pic")
public class BookPic {
    @Id
    private Integer id;

    private String base64;

    public BookPic(int id, String base64) {
        this.id = id;
        this.base64 = base64;
    }

    public String getBase64() {
        return base64;
    }

    public void setBase64(String base64) {
        this.base64 = base64;
    }

}
