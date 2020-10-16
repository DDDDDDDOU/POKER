package com.example.last.repository;

import com.example.last.entity.Orde;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface OrderRepository extends JpaRepository<Orde,Integer> {
        @Query(value="select o from Orde o where o.userid=?1")
        List<Orde>  readOrder(Integer userid);

        @Query(value="select o from Orde o ")
        List<Orde> readOrderBySuper();


}
