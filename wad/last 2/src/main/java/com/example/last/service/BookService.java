package com.example.last.service;

import com.example.last.entity.Book;

import java.util.List;


public interface BookService {

    Book findBookById(Integer id);
    void updateBook(Integer id,String name,String price,String des);

    List<Book> getBooks();
}
