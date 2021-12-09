package com.xmall.xmall.dao.mapper;

import com.rabbitmq.client.Address;
import com.xmall.xmall.dao.entity.AddressEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;

import java.util.List;
import java.util.Optional;


public interface UserInfoMapper {
    /*
    * 查询所有用户
    * @return 返回用户集合
    */
    List<UserInfoEntity> findAll();

    Optional<UserInfoEntity> findByUuid(String uuid);

    Optional<UserInfoEntity> findById(int id);

    Optional<UserInfoEntity> findByPhone(String phone);

    boolean updateByPhone(UserInfoEntity userInfoEntity);

    int saveUser(UserInfoEntity userInfoEntity);

    boolean updateAvatarByPhone(String phone,String path);

    //Address
    List<AddressEntity> findAllAddressByPhone(String userPhone);
    int saveAddress(AddressEntity addressEntity);
}
