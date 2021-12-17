package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.CartEntity;

import java.util.List;

public interface CartService {
    List<CartEntity> getAllActiveByPhone(String phone) throws Exception;
    CartEntity getById(long id) throws Exception;
    int checkById(long id, String phone) throws Exception;
    int disCheckById(long id, String phone) throws Exception;
    int  lazyDeleteById(long id, String phone) throws Exception;
    int updateCountById(CartEntity cartEntity) throws Exception;
    int insertCart(CartEntity cartEntity) throws Exception;
    double calculate(List<CartEntity> cartEntityList) throws Exception;
}
