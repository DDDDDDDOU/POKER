package com.example.last.controller;
import com.example.last.entity.Book;
import com.example.last.entity.Orde;
import com.example.last.service.CartService;
import com.example.last.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
public class OrderController {
    @Autowired
    private CartService cartService;
    @Autowired
    private OrderService orderService;

    @RequestMapping("/readOrder")
    public List<Orde> readOrder(@RequestBody Map<String, Integer> params){

        return orderService.readOrder(params.get("userid"));
    }

    @RequestMapping("/readOrderBySuper")
    public List<Orde> readOrderBySuper(){
        System.out.println("read by super");
        return orderService.readOrderBySuper();
    }


}