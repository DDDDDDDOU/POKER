package com.example.last.serviceimpl;

import com.example.last.dao.BookDao;
import com.example.last.entity.Book;
import com.example.last.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;


@Service
public class BookServiceImpl implements BookService {

    @Autowired
    private BookDao bookDao;

    @Override
    public Book findBookById(Integer id){
        return bookDao.findOne(id);
    }

    @Override
    public List<Book> getBooks() {
        return bookDao.getBooks();
    }
    @Override
    public void updateBook(Integer id,String name,String price,String des){
        System.out.println(name);
        System.out.println(price);
        System.out.println(des);
        bookDao.update(id,name,price,des);
    }

    @Override
    public void delete(Integer bookid){
        bookDao.delete(bookid);
    }
}
