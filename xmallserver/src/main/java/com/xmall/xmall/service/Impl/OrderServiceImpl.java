package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.mapper.OrderMapper;
import com.xmall.xmall.dao.mapper.ProductMapper;
import com.xmall.xmall.service.OrderService;
import com.xmall.xmall.utils.RedisUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 3:09
 * Version V1.0
 */
@Service
@Slf4j
public class OrderServiceImpl implements OrderService {
    @Resource
    private OrderMapper orderMapper;
    @Autowired
    private RedisUtil redisUtil;

    @Override
    public OrderEntity getById(long id) throws Exception {
        return orderMapper.findById(id)
                .orElseThrow(() -> new Exception("NOT_FOUND"));
    }

    @Override
    public OrderEntity getBySn(String orderSn) throws Exception {
        return orderMapper.findBySn(orderSn)
                .orElseThrow(() -> new Exception("NOT_FOUND"));
    }
}
