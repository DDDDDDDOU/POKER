package com.example.last.daoimpl;

import com.example.last.dao.BookDao;
import com.example.last.dao.CartDao;
import com.example.last.dao.OrderDao;
import com.example.last.dao.UserDao;
import com.example.last.entity.*;
import com.example.last.repository.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public class OrderDaoImpl implements OrderDao {
    @Autowired
    OrderRepository orderRepository;
    @Autowired
    BookDao bookDao;
    @Autowired
    UserDao userDao;
    @Autowired
    private BookPicRepository bookPicRepository;
    @Autowired
    UserAuthRepository userAuthRepository;

    @Override
    public  List<Orde> readOrder(int userid){
        List<Orde> o=orderRepository.readOrder(userid);

        for(int i=0;i<o.size();++i){
            o.get(i).setb(bookDao.findOne(o.get(i).getBookid()) );
            o.get(i).setu(userAuthRepository.getOne(o.get(i).getUserid()));
            System.out.println(o.get(i).getu());
        }
        return o;

    }

    @Override
    public  List<Orde> readOrderBySuper(){
        List<Orde> o=orderRepository.readOrderBySuper();

        for(int i=0;i<o.size();++i){
            Book b=bookDao.findOne(o.get(i).getBookid());
            o.get(i).setb(b);
            o.get(i).setu(userAuthRepository.getOne(o.get(i).getUserid()));
            System.out.println(o.get(i).getu());
        }
        return o;
    }



}
