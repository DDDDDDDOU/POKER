package com.example.last.daoimpl;

import com.example.last.dao.UserDao;
import com.example.last.entity.User;
import com.example.last.entity.UserAuth;
import com.example.last.repository.UserAuthRepository;
import com.example.last.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import java.util.List;
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

    @Override
    public UserAuth getUser(int userid){
       UserAuth u=userAuthRepository.getOne(userid);
       u.setPassword("");
       return u;
    }

    @Override
    public List<UserAuth> getUsers(){
        List<UserAuth> u=userAuthRepository.getUsers();
        for(int i=0;i<u.size();++i){
            u.get(i).setPassword("");
        }
        return u;
    }

    @Override
    public void banuser(Integer userid,Integer allow){
        UserAuth u=userAuthRepository.getOne(userid);
        System.out.println("begin ban");
        if(u.getAuthentic()==allow) return;
        u.setAuthentic(allow);
        userAuthRepository.save(u);

    }

    @Override
    public Integer register(String username,String password,String mail){
        UserAuth u=userAuthRepository.getByName(username);
        if(u!=null) return 0;
        else{
            UserAuth user=new UserAuth();
            user.setAuthentic(1);
            user.setUsername(username);
            user.setPassword(password);
            user.setUserType(1);
            user.setMail(mail);
            userAuthRepository.save(user);
            return 1;

        }
    }

}
