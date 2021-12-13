package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.AdminEntity;


import java.util.Optional;

public interface AdminMapper {
    Optional<AdminEntity> findByPhone(String phone);
    int saveAdmin(AdminEntity adminEntity);
}
