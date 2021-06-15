package com.example.last.controller;

import com.example.last.entity.UserAuth;
import com.example.last.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class UserController {

    @Autowired
    private UserService userService;

    @RequestMapping("/checkUser")
    public UserAuth checkUser(@RequestParam("username") String username, @RequestParam("password") String password){

        System.out.println(username);
        return userService.checkUser(username, password);
    }



}
