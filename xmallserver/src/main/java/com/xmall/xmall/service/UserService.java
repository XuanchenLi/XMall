package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.NotFoundException;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;


public interface UserService {


    UserInfoEntity getByUuid(String uuid) throws NotFoundException;
    UserInfoEntity getById(int id) throws NotFoundException;
    UserInfoEntity getByPhone(String phone) throws NotFoundException;
    List<UserInfoEntity> getAll();
    int register(UserInfoDto userInfoDto);

}
