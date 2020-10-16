package com.example.last.repository;

import com.example.last.entity.UserAuth;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface UserAuthRepository extends JpaRepository<UserAuth,String> {

    @Query(value = "from UserAuth where username = :username and password = :password")
    UserAuth checkUser(@Param("username") String username, @Param("password") String password);

    @Query(value="select  u from UserAuth u where u.userId=?1")
    UserAuth getOne(Integer userid);

    @Query(value="select u from UserAuth  u")
    List<UserAuth> getUsers();

    @Query(value="select  u from UserAuth u where u.username=?1")
    UserAuth getByName(String username);
}
