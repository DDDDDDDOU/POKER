package com.example.last.daoimpl;

import com.example.last.dao.BookDao;
import com.example.last.dao.CartDao;
import com.example.last.entity.*;
import com.example.last.repository.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Optional;

@Repository
public class CartDaoImpl implements CartDao {
    @Autowired
    CartRepository cartRepository;
    @Autowired
    BookRepository bookRepository;
    @Autowired
    BookDao bookDao;
    @Autowired
    private BookPicRepository bookPicRepository;
    @Autowired
    private UserAuthRepository userAuthRepository;
    @Autowired
    private OrderRepository orderRepository;

    @Override
    public void addOne(Integer userid,Integer bookid){
        Cart a=cartRepository.getCart(userid,bookid);
        System.out.println(a);
        Cart c=new Cart();
        if(a!=null) {
            c.setId(a.getId());
            c.setnum(a.getnum()+1);
        }
        else c.setnum(1);
        c.setbookid(bookid);
        c.setuserid(userid);

        cartRepository.save(c);
    }

    @Override
    public List<Book> read(Integer userid)
    {
        System.out.println("Dao:");
       // return cartRepository.read(userid) ;
        List<Book> books= cartRepository.read(userid);

        System.out.println(books);
        for(int i =0;i<books.size();++i){
            System.out.println(books.get(i).getBookId());
            Optional<BookPic> pic=bookPicRepository.findById( books.get(i).getBookId());
            if(pic.isPresent()){
                books.get(i).setPic(pic.get().getBase64());
            }
            books.get(i).setnum(cartRepository.getnum(userid,books.get(i).getBookId()));
        }
        return books;
    }

    @Override
    public void updateCart(Integer num,Integer userid,Integer bookid){
        Cart c=cartRepository.getCart(userid,bookid);
        c.setnum(num);
        cartRepository.save(c);

    }

    @Override
    public  void buy(Integer userid){
        System.out.println("begin buy");
        List<Cart> carts=cartRepository.readByUserid(userid);
        System.out.println(carts);

        SimpleDateFormat sdf =new SimpleDateFormat("yyyy年MM月dd日HH时mm分ss秒SS" );
        SimpleDateFormat sdf2 =new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss" );
        Date d= new Date();
        String str = sdf.format(d);
        NumberFormat formatter =
                NumberFormat.getNumberInstance();
        formatter.setMinimumIntegerDigits(3);//3位数bai，前du面zhi补dao0
        formatter.setGroupingUsed(false);
        String orderid = formatter.format(userid);//n=14,s=014
        orderid+=sdf2.format(d);

        for(int i=0;i<carts.size();++i){
            if(carts.get(i).getnum()!=0){
                Orde ord=new Orde();
                UserAuth u=userAuthRepository.getOne(carts.get(i).getuserid());
                Book b=bookRepository.getOne(carts.get(i).getbookid());
                b.setInventory(b.getInventory()-carts.get(i).getnum());
                u.setNum(u.getNum()+carts.get(i).getnum());
                Double cost= Double.parseDouble(b.getPrice());
                cost*=(double) carts.get(i).getnum();
                u.setCost(""+(Double.parseDouble(u.getCost())+cost));
                bookRepository.save(b);
                ord.setbookid(carts.get(i).getbookid());
                ord.setuserid(carts.get(i).getuserid());
                ord.setnum(carts.get(i).getnum());
                ord.setUsername(u.getUsername());
                ord.setorderid(orderid);

                ord.setBuytime(str);
                System.out.println("o:"+ord);
                orderRepository.save(ord);
                userAuthRepository.save(u);
            }

            cartRepository.deleteById(carts.get(i).getId());

        }
    }

}
