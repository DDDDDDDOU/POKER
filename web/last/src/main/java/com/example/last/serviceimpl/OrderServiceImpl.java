package com.example.last.serviceimpl;

import com.example.last.dao.BookDao;
import com.example.last.dao.CartDao;
import com.example.last.dao.OrderDao;
import com.example.last.entity.Book;
import com.example.last.entity.Orde;
import com.example.last.service.BookService;
import com.example.last.service.CartService;
import com.example.last.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class OrderServiceImpl implements OrderService {
    @Autowired
    private OrderDao orderDao;

    @Override
    public List<Orde> readOrder(int userid){
        return orderDao.readOrder(userid);
    }

    @Override
    public List<Orde> readOrderBySuper(){
        return orderDao.readOrderBySuper();
    }
}
