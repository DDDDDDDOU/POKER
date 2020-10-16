package com.example.last.controller;
import com.example.last.entity.Book;
import com.example.last.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;


@RestController
public class BookController {

    @Autowired
    private BookService bookService;

    @RequestMapping("/getBooks")
    public List<Book> getBooks(@RequestBody Map<String, String> params) {
        return bookService.getBooks();
    }

    @RequestMapping("/getBook")
    public Book getBook(@RequestParam("id") Integer id){
        return bookService.findBookById(id);
    }
    @RequestMapping("/updateBook")
    public int updateBooks(@RequestBody Map<String,String> params){
        System.out.println("update:");
        System.out.println(params);
        bookService.updateBook(Integer.valueOf(params.get("bookId")), params.get("name"),params.get("price"),params.get("description"));
        return  1;
    }
}
