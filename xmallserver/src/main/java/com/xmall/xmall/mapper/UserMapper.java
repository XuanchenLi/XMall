package com.xmall.xmall.mapper;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import org.mapstruct.Mapper;
import org.mapstruct.factory.Mappers;

@Mapper
public interface UserMapper {
    UserMapper INSTANCE = Mappers.getMapper( UserMapper.class );

    UserInfoDto userInfoEntityToDto(UserInfoEntity userInfoEntity);
}
