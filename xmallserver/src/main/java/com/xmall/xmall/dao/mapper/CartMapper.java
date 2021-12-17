package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.CartEntity;

import java.util.List;
import java.util.Optional;

public interface CartMapper {
    List<CartEntity> findAllActiveByPhone(String phone) throws Exception;
    CartEntity findById(long id) throws Exception;
    int checkById(long id) throws Exception;
    int disCheckById(long id) throws Exception;
    int lazyDeleteById(long id) throws  Exception;
    int updateCountById(int count, long id) throws  Exception;
    int saveCart(CartEntity cartEntity) throws Exception;

}
