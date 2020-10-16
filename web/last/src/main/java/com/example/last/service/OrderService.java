package com.example.last.service;

import com.example.last.entity.Orde;


import java.util.List;
public interface OrderService {
    List<Orde> readOrder(int userid);

    List<Orde> readOrderBySuper();
}
