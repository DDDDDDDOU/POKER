package com.example.last.service;

import com.example.last.entity.UserAuth;
import java.util.List;

public interface UserService {

    UserAuth checkUser(String username, String password);
    List<UserAuth> getUsers();
    void banuser(Integer userid,Integer allow);
    Integer register(String username,String password,String mail);
}
