package com.example.last.daoimpl;

import com.example.last.dao.BookDao;
import com.example.last.dao.CartDao;
import com.example.last.entity.Book;
import com.example.last.entity.Cart;
import com.example.last.repository.BookRepository;
import com.example.last.repository.CartRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;
@Repository
public class CartDaoImpl implements CartDao {
    @Autowired
    CartRepository cartRepository;
    @Autowired
    BookDao bookDao;

    @Override
    public void addOne(Integer userid,Integer bookid){

        Cart c=new Cart();
        c.setbookid(bookid);
        c.setuserid(userid);
        cartRepository.save(c);
    }

    @Override
    public List<Book> read(Integer userid)
    {
        System.out.println("Dao:");
        return cartRepository.read(userid) ;
    }


}
