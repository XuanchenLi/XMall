package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.AdminEntity;
import com.xmall.xmall.exception.NotFoundException;

public interface AdminService {
    AdminEntity getByPhone(String phone) throws NotFoundException;
    int register(AdminEntity adminEntity);
}
