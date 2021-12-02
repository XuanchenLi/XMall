package com.xmall.xmall.controller;

import com.alibaba.fastjson.JSON;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.xmall.xmall.controller.response.RegistrationResponse;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.BadRequestException;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.UserService;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StatusEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 1:21
 * Version V1.0
 */

@RestController
@RequestMapping("/user")
public class UserInfoController {
    @Autowired
    private UserService userService;
    @Autowired
    private RedisUtil redisUtil;

    private static final  String key = "userCache_";

    @GetMapping("/")
    List<UserInfoDto> getAllUser() throws JsonProcessingException {
        List<UserInfoEntity> userInfoEntityList = null;
        if (redisUtil.exists(key + "UserList"))
        {
            userInfoEntityList = JSON.parseArray((String) redisUtil.get(key + "UserList"), UserInfoEntity.class);
        }
        if(userInfoEntityList == null) {//不在缓存中
            List<UserInfoEntity> userInfoList = userService.getAll();//从数据库获取
            if (!userInfoList.isEmpty())
            {
                String usersJson = new ObjectMapper().writeValueAsString(userInfoList);
                redisUtil.set(key + "UserList", usersJson, Constants.CACHE_30MINS);
                //redisUtil.setExpire(key + "UserList", 30, TimeUnit.MINUTES);
                return userInfoList
                        .stream()
                        .map(UserMapper.INSTANCE::userInfoEntityToDto)
                        .collect(Collectors.toList());
            }
        }
        return userInfoEntityList
                .stream()
                .map(UserMapper.INSTANCE::userInfoEntityToDto)
                .collect(Collectors.toList());
    }

    @GetMapping("/uuid/{uuid}")
    UserInfoDto getByUuid(@PathVariable("uuid") String uuid) throws NotFoundException {
        UserInfoEntity userInfoEntity = (UserInfoEntity) redisUtil.get(key + "Uuid_" +uuid);
        if(userInfoEntity == null) {//不在缓存中
            UserInfoEntity userInfo = userService.getByUuid(uuid);//从数据库获取
            if (userInfo != null)
            {
                redisUtil.set(key + "Uuid_" + uuid, userInfo, Constants.CACHE_1MIN);
                return UserMapper.INSTANCE.userInfoEntityToDto(userInfo);
            }
        }
        return UserMapper.INSTANCE.userInfoEntityToDto(userInfoEntity);
    }

    @GetMapping("/id/{id}")
    UserInfoDto getById(@PathVariable("id") int id) throws NotFoundException {
        UserInfoEntity userInfoEntity = (UserInfoEntity) redisUtil.get(key + "Id_" +id);
        if(userInfoEntity == null) {//不在缓存中
            UserInfoEntity userInfo = userService.getById(id);//从数据库获取
            if (userInfo != null)
            {
                redisUtil.set(key + "Id_" + id, userInfo, Constants.CACHE_1MIN);
                return UserMapper.INSTANCE.userInfoEntityToDto(userInfo);
            }
        }

        return UserMapper.INSTANCE.userInfoEntityToDto(userInfoEntity);
    }

    @PostMapping("/register")
    RegistrationResponse register(@RequestBody UserInfoDto userInfoDto) throws BadRequestException {
        if(userService.register(userInfoDto) == -1)
        {
            return new RegistrationResponse(StatusEnum.BAD_REQUEST);
        }
        return new RegistrationResponse(StatusEnum.SUCCESS);
    }
}
