package com.example.last.repository;
import com.example.last.entity.BookPic;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;
public interface BookPicRepository extends MongoRepository<BookPic,Integer>{

}
