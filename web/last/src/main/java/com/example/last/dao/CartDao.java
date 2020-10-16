package com.example.last.dao;

import com.example.last.entity.Book;

import java.util.List;

public interface CartDao {
    void addOne(Integer userid,Integer bookid);

    List<Book> read(Integer userid);

    void updateCart(Integer num,Integer userid,Integer bookid);

    void buy(Integer userid);


}
