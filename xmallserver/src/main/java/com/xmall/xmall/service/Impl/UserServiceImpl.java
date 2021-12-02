package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dao.mapper.UserInfoMapper;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.messagingService.UserMessagingService;
import com.xmall.xmall.service.UserService;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.StringUtil;
import lombok.extern.slf4j.Slf4j;
import org.joda.time.DateTimeUtils;
import org.mapstruct.ap.shaded.freemarker.template.utility.DateUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CachePut;
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

    @Autowired
    UserMessagingService userMessagingService;
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

    @Override
    public int register(UserInfoDto userInfoDto) {

        UserInfoEntity userInfoEntity = UserMapper.INSTANCE.userInfoDtoToEntity(userInfoDto);
        userInfoEntity.setRegisterTime(DateTimeUtil.getTimestamp());
        userInfoEntity.setUuid(StringUtil.allocateUuid());

        try{
            return  userInfoMapper.saveUser(userInfoEntity);//成功则返回插入数据条数
        }catch (Exception e )
        {
            return -1;
        }

    }
}
