package com.example.last.controller;
import com.example.last.entity.Book;
import com.example.last.service.CartService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
public class CartController {
    @Autowired
    private CartService cartService;

    @RequestMapping("/readCart")
    public List<Book> readCart(@RequestBody Map<String, Integer> params) {
        System.out.println(params.get("userid"));
        return cartService.readcart(params.get("userid"));
    }

    @RequestMapping("/addCart")
    public int addCart(@RequestBody Map<String, Integer> params){
        cartService.addCart(params.get("userid"), params.get("bookid"));
        return 1;
    }

}
