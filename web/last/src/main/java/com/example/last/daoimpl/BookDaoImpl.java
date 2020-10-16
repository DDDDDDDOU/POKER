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

        Optional<BookPic> pic=bookPicRepository.findById(id);
        System.out.println("find one:");
        System.out.println(book);
        if(pic.isPresent()){
            book.setPic(pic.get().getBase64());
        }
        return book;
    }


    @Override
    public List<Book> getBooks() {
        List<Book> books= bookRepository.getBooks();
        System.out.println(books);
        for(int i =0;i<books.size();++i){
            books.get(i).setsale();
            System.out.println(books.get(i).getBookId());
            Optional<BookPic> pic=bookPicRepository.findById( books.get(i).getBookId());
            System.out.println(pic.get().getBase64());
            if(pic.isPresent()){
                books.get(i).setPic(pic.get().getBase64());

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

    @Override
    public void delete(Integer bookid){
        bookRepository.deleteById(bookid);
    }
}
