package com.example.last.controller;

import com.example.last.entity.UserAuth;
import com.example.last.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;


@RestController
public class UserController {

    @Autowired
    private UserService userService;

    @RequestMapping("/checkUser")
    public UserAuth checkUser(@RequestParam("username") String username, @RequestParam("password") String password){

        System.out.println(username);
        return userService.checkUser(username, password);
    }
    @RequestMapping("/getUsers")
    public List<UserAuth> getUsers(){return userService.getUsers();}

    @RequestMapping("/ban")
    public int banuser(@RequestBody Map<String, Integer> params){
        userService.banuser(params.get("userid"),params.get("allow"));
        return 1;
    }
    @RequestMapping("/register")
    public int register(@RequestBody Map<String, String> params){
       int i= userService.register(params.get("username"),params.get("password"),params.get("mail"));
       return i;

    }



}
