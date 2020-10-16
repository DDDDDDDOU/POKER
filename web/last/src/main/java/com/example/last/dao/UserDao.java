package com.example.last.dao;

import com.example.last.entity.UserAuth;
import java.util.List;
public interface UserDao {

    UserAuth checkUser(String username, String password);
     UserAuth getUser(int userid);
     List<UserAuth> getUsers();
    void banuser(Integer userid,Integer allow);
    Integer register(String username,String password,String mail);
}
