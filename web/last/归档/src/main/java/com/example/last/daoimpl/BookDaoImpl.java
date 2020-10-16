package com.example.last.daoimpl;

import com.example.last.dao.BookDao;
import com.example.last.entity.Book;
import com.example.last.entity.BookPic;
import com.example.last.repository.BookPicRepository;
import com.example.last.repository.BookRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import javax.swing.text.html.Option;
import java.util.List;
import java.util.Optional;


@Repository
public class BookDaoImpl implements BookDao {

    @Autowired
    private BookRepository bookRepository;
    @Autowired
    private BookPicRepository bookPicRepository;

    @Override
    public Book findOne(Integer id){
        Book book= bookRepository.getOne(id);

        return book;
    }


    @Override
    public List<Book> getBooks() {
        List<Book> books= bookRepository.getBooks();
        for(int i =0;i<books.size();++i){
            Optional<BookPic> pic=bookPicRepository.findById(books.get(i).getBookId() );
            if(pic.isPresent()){
                books.get(i).setBookPic(pic.get());
            }

        }
        return books;
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
