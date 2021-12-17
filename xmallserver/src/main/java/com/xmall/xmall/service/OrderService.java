package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.OrderEntity;

public interface OrderService {
    OrderEntity getById(long Id) throws Exception;
    OrderEntity getBySn(String orderSn) throws Exception;
}
