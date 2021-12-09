package com.xmall.xmall.service.Impl;

import com.xmall.xmall.controller.response.UserInfoEntityResponse;
import com.xmall.xmall.dao.entity.AddressEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dao.mapper.UserInfoMapper;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.BadRequestException;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.messagingService.UserMessagingService;
import com.xmall.xmall.service.UserService;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StringUtil;
import lombok.extern.slf4j.Slf4j;
import org.apache.tomcat.util.bcel.Const;
import org.joda.time.DateTimeUtils;
import org.mapstruct.ap.shaded.freemarker.template.utility.DateUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CachePut;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;
import java.util.Optional;

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

    @Autowired
    private RedisUtil redisUtil;

    @Override
    @Cacheable(cacheNames = Constants.ONE_MINUTE, key ="'USER_Uuid_'+#uuid", unless = "#result == null")
    public UserInfoEntity getByUuid(String uuid) throws NotFoundException {

        return userInfoMapper.findByUuid(uuid)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

    @Override
    public List<UserInfoEntity> getAll() {
        return userInfoMapper.findAll();
    }

    @Override
    @Cacheable(cacheNames = Constants.ONE_MINUTE, key ="'USER_Id_'+#id", unless = "#result == null")
    public UserInfoEntity getById(int id) throws NotFoundException {

        return userInfoMapper.findById(id)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

    @Override
    @Cacheable(cacheNames = Constants.ONE_MINUTE, key ="'USER_Phone_'+#phone", unless = "#result == null")
    public UserInfoEntity getByPhone(String phone) throws NotFoundException {
        return userInfoMapper.findByPhone(phone)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

    @Override
    @CachePut(cacheNames = Constants.ONE_MINUTE, key ="'USER_Phone_'+#userInfoEntity.phone", unless = "#result == null")
    public UserInfoEntity updateInfoByPhone(UserInfoEntity userInfoEntity) throws NotFoundException , BadRequestException {

        UserInfoEntity oldUserInfoEntity = getByPhone(userInfoEntity.getPhone());
        try {
            userInfoEntity.setUuid(oldUserInfoEntity.getUuid());
            userInfoEntity.setRegisterTime(oldUserInfoEntity.getRegisterTime());
            userInfoEntity.setId(oldUserInfoEntity.getId());
            userInfoEntity.setIcon(oldUserInfoEntity.getIcon());
            userInfoEntity.setPassword(oldUserInfoEntity.getPassword());
            if (userInfoMapper.updateByPhone(userInfoEntity)) {
                return userInfoEntity;
            }
            else
            {
                throw new BadRequestException("更新失败");
            }
        }catch (Exception e) {
            throw new BadRequestException("更新失败");
        }
    }

    @Override
    public int register(UserInfoDto userInfoDto) {
        UserInfoEntity userInfoEntity = UserMapper.INSTANCE.userInfoDtoToEntity(userInfoDto);
        userInfoEntity.setEmail(userInfoDto.getEmail());
        userInfoEntity.setRegisterTime(DateTimeUtil.getTimestamp());
        userInfoEntity.setUuid(StringUtil.allocateUuid());

        Optional<UserInfoEntity> userInfo = userInfoMapper.findByPhone(userInfoDto.getPhone());
        if(userInfo.isPresent())
        {
            return -1;
        }
        try{
            return userInfoMapper.saveUser(userInfoEntity);
        }catch (Exception e)
        {
            return -1;
        }
    }

    @Override
    @CachePut(cacheNames = Constants.ONE_MINUTE, key ="'USER_Phone_'+#userInfoEntity.phone", unless = "#result == null")
    public UserInfoEntity updateAvatarByPhone(UserInfoEntity userInfoEntity) throws NotFoundException, BadRequestException {
        userInfoMapper.updateAvatarByPhone(userInfoEntity.getPhone(), userInfoEntity.getIcon());
        return userInfoEntity;
    }

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'ADDRESSES_Phone_'+#userPhone", unless = "#result == null")
    public List<AddressEntity> getAllAddressByPhone(String userPhone) throws NotFoundException {
        return userInfoMapper.findAllAddressByPhone(userPhone);
    }

    @Override
    public int saveAddress(AddressEntity addressEntity) {
        redisUtil.remove("ADDRESSES_Phone_" + addressEntity.getUserPhone());
        try {
            return userInfoMapper.saveAddress(addressEntity);
        }catch (Exception e)
        {
            return 0;
        }
    }

}
