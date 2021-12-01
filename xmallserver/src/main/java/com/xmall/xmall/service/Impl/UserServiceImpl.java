package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dao.mapper.UserInfoMapper;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.NormalException;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 12:15
 * Version V1.0
 */
@Service
@Slf4j
public class UserServiceImpl implements UserService {
    @Resource
    private UserInfoMapper userInfoMapper;

    @Override
    public UserInfoEntity getByUuid(String uuid) throws NotFoundException {

        return userInfoMapper.findByUuid(uuid)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

    @Override
    public List<UserInfoEntity> getAll() {
        return userInfoMapper.findAll();
    }

    @Override
    public UserInfoEntity getById(int id) throws NotFoundException {

        return userInfoMapper.findById(id)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

}
