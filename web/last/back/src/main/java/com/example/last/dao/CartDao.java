package com.example.last.dao;

import com.example.last.entity.Book;

import java.util.List;

public interface CartDao {
    void addOne(Integer userid,Integer bookid);
    List<Book> read(Integer userid);

}
