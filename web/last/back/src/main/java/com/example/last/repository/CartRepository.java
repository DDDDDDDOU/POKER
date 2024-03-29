package com.example.last.repository;

import com.example.last.entity.Cart;
import com.example.last.entity.Book;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface CartRepository extends JpaRepository<Cart,Integer> {
    @Query(value="select b from Cart c left join Book b on c.bookid=b.bookId where c.userid=?1")
    List<Book> read(@Param("userid") Integer userid);

//    @Modifying(clearAutomatically=true)
//        @Query(value="insert into cart(userid,bookid) value(?1,?2)",nativeQuery=true)
//        void addOne(@Param("userid") Integer userid,@Param("bookid") Integer bookid);
}
