package com.example.last.dao;

import com.example.last.entity.UserAuth;

public interface UserDao {

    UserAuth checkUser(String username, String password);
}
