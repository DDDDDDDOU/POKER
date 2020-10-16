package com.example.last.daoimpl;

import com.example.last.dao.UserDao;
import com.example.last.entity.UserAuth;
import com.example.last.repository.UserAuthRepository;
import com.example.last.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

@Repository
public class UserDaoImpl implements UserDao {

    @Autowired
    UserAuthRepository userAuthRepository;

    @Autowired
    UserRepository userRepository;

    @Override
    public UserAuth checkUser(String username, String password){

        return userAuthRepository.checkUser(username,password);
    }


}
