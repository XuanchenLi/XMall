package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;

import java.util.List;

public interface OrderService {
    OrderEntity getById(long Id) throws Exception;
    OrderEntity getBySn(String orderSn) throws Exception;
    List<OrderItemEntity> getAllItemBySn(String orderSn) throws Exception;
}
