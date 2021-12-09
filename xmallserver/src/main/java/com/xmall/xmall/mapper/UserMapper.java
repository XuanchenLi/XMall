package com.xmall.xmall.mapper;

import com.xmall.xmall.controller.request.EditUserInfoRequest;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import org.mapstruct.Mapper;
import org.mapstruct.factory.Mappers;

@Mapper
public interface UserMapper {
    UserMapper INSTANCE = Mappers.getMapper( UserMapper.class );

    UserInfoEntity editUserInfoRequestToEntity(EditUserInfoRequest editUserInfoRequest);
    UserInfoDto userInfoEntityToDto(UserInfoEntity userInfoEntity);
    UserInfoEntity userInfoDtoToEntity(UserInfoDto userInfoDto);
}
