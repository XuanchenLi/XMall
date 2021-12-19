package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.CartEntity;
import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;
import org.springframework.core.annotation.Order;

import java.util.List;

public interface OrderService {
    OrderEntity getById(long Id) throws Exception;
    OrderEntity getBySn(String orderSn) throws Exception;
    List<OrderItemEntity> getAllItemBySn(String orderSn) throws Exception;
    OrderEntity newOrder(String phone) throws Exception;
    int saveItem(OrderItemEntity orderItemEntity) throws Exception;
    int saveItems(List<OrderItemEntity> orderItemEntityList) throws Exception;
    double calculate(List<OrderItemEntity> orderItemEntityList) throws Exception;
    int pay(OrderEntity orderEntity) throws Exception;
}
