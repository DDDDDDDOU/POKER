package com.example.last.dao;

import com.example.last.entity.Book;
import com.example.last.entity.Orde;

import java.util.List;

public interface OrderDao {
    List<Orde> readOrder(int userid);
    List<Orde> readOrderBySuper();
}
