package com.xmall.xmall.controller;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
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
public class UserAdminController {
    @Autowired
    private UserService userService;

    @GetMapping("/")
    List<UserInfoDto> getAllUser() {
        //System.out.println(userService.getAll());
        return userService.getAll()
                .stream()
                .map(UserMapper.INSTANCE::userInfoEntityToDto)
                .collect(Collectors.toList());
    }

    @GetMapping("/uuid/{uuid}")
    UserInfoDto getByUuid(@PathVariable("uuid") String uuid) throws NotFoundException {
        //System.out.println(uuid);
        return UserMapper.INSTANCE.userInfoEntityToDto(userService.getByUuid(uuid));
    }

    @GetMapping("/id/{id}")
    UserInfoDto getById(@PathVariable("id") int id) throws NotFoundException {
        //System.out.println(uuid);
        //return UserMapper.INSTANCE.userInfoEntityToDto(userService.getById(id));
        UserInfoDto user = new UserInfoDto();
        user.setNickname("Dazzl");
        user.setPassword("12");
        user.setPhone("12");
        user.setUuid("assa");
        return user;
    }
}
