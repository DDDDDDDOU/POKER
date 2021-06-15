package com.example.last.service;

import com.example.last.entity.UserAuth;


public interface UserService {

    UserAuth checkUser(String username, String password);
}
