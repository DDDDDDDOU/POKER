package com.example.last.serviceimpl;

import com.example.last.dao.BookDao;
import com.example.last.dao.CartDao;
import com.example.last.entity.Book;
import com.example.last.service.BookService;
import com.example.last.service.CartService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CartServiceImpl implements CartService {
    @Autowired
    private CartDao cartDao;

    @Override
    public void addCart(Integer userid, Integer bookid){

         cartDao.addOne(userid,bookid);
    }
    @Override
    public List<Book> readcart(Integer userid){
        System.out.println("Cart Service:");
        return cartDao.read(userid);
    }

}
