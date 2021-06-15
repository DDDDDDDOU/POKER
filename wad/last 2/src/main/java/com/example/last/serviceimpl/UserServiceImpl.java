package com.example.last.serviceimpl;

import com.example.last.dao.UserDao;
import com.example.last.entity.UserAuth;
import com.example.last.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserDao userDao;

    @Override
    public UserAuth checkUser(String username, String password){
        return userDao.checkUser(username,password);


    }
}
