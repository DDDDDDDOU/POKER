package com.example.last.daoimpl;

import com.example.last.dao.BookDao;
import com.example.last.entity.Book;
import com.example.last.repository.BookRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;


@Repository
public class BookDaoImpl implements BookDao {

    @Autowired
    private BookRepository bookRepository;

    @Override
    public Book findOne(Integer id){
        return bookRepository.getOne(id);
    }


    @Override
    public List<Book> getBooks() {
        return bookRepository.getBooks();
    }

    @Override
    public    void update(Integer id,String n,String p,String d){
        Book b=bookRepository.getOne(id);
        System.out.println("change:"+b);
        b.setname(n);
        b.setprice(p);
        b.setdescription(d);
        bookRepository.save(b);

    }


}
