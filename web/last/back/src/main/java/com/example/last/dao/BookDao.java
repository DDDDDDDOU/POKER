package com.example.last.dao;

import com.example.last.entity.Book;

import java.util.List;

public interface BookDao {
    Book findOne(Integer id);

    List<Book> getBooks();
    void update(Integer id,String n,String p,String d);
}
