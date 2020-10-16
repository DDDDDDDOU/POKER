package com.example.last.service;

import com.example.last.entity.Book;

import java.lang.reflect.Array;
import java.util.List;
public interface CartService {
    void addCart(Integer userid, Integer bookid);

    List<Book> readcart(Integer userid);

    void updateCart(Integer userid,Integer bookid, Integer num);

    void buy(Integer userid);
}
