package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.CartEntity;
import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;
import com.xmall.xmall.dao.entity.ProductEntity;
import com.xmall.xmall.dao.mapper.OrderMapper;
import com.xmall.xmall.dao.mapper.ProductMapper;
import com.xmall.xmall.message.ProductSaleMessage;
import com.xmall.xmall.service.OrderService;
import com.xmall.xmall.service.ProductService;
import com.xmall.xmall.service.messagingService.ProductMessagingService;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StringUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.*;

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
    @Autowired
    private ProductService productService;
    @Autowired
    private ProductMessagingService productMessagingService;

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

    @Override
    public List<OrderItemEntity> getAllItemBySn(String orderSn) throws Exception {
        return orderMapper.findAllItemBySn(orderSn);
    }

    @Override
    public OrderEntity newOrder(String phone) throws Exception {
        OrderEntity orderEntity = new OrderEntity();
        orderEntity.setOrderSn(StringUtil.allocateUuid());
        orderEntity.setUserPhone(phone);
        orderEntity.setCreatTime(DateTimeUtil.getTimestamp());
        orderEntity.setStatus(0);
        orderMapper.saveOrder(orderEntity);
        return orderEntity;
    }

    @Override
    public int saveItem(OrderItemEntity orderItemEntity) throws Exception {
        ProductEntity oldProduct = productService.getById(orderItemEntity.getProductId());
        long  storage = oldProduct.getStorage();
        if(orderItemEntity.getCount() > storage)
        {
            return 0;
        }
        productService.updateStorageById(storage - orderItemEntity.getCount(), oldProduct.getId());
        return orderMapper.saveOrderItem(orderItemEntity);
    }

    @Override
    public int saveItems(List<OrderItemEntity> orderItemEntityList) throws Exception {
        List<ProductEntity> productEntityList = new ArrayList<>();
        for (OrderItemEntity item : orderItemEntityList)
        {
            ProductEntity oldProduct = productService.getById(item.getProductId());
            if(item.getCount() > oldProduct.getStorage())
            {
                throw new Exception("超限");
            }
            productEntityList.add(oldProduct);
        }
        int res = 0, i =0;
        for (OrderItemEntity item : orderItemEntityList)
        {
            productService.updateStorageById(productEntityList.get(i).getStorage() - item.getCount(), productEntityList.get(i).getId());
            res += orderMapper.saveOrderItem(item);
        }
        return res;
    }

    @Override
    public double calculate(List<OrderItemEntity> orderItemEntityList) throws Exception {
        double res = 0;
        for (int i = 0; i < orderItemEntityList.size(); ++i)
        {
            OrderItemEntity orderItemEntity = orderItemEntityList.get(i);
            ProductEntity productEntity = productService.getById(orderItemEntity.getProductId());
            if(productEntity.getStatus() == 1&& (productEntity.getLimitation() >= orderItemEntity.getCount())
                    || productEntity.getLimitation() == -1)
            {
                res += orderItemEntity.getCount() * productEntity.getCurrentPrice();
            }
            else {
                return -1;
            }
        }
        return res;
    }

    @Override
    public int pay(OrderEntity orderEntity) throws Exception {
        //异步更新销售额
        List<OrderItemEntity> orderItemEntityList = getAllItemBySn(orderEntity.getOrderSn());
        for (OrderItemEntity item : orderItemEntityList) {
            ProductSaleMessage productSaleMessage = new ProductSaleMessage();
            productSaleMessage.setProductId(item.getProductId());
            productSaleMessage.setSale(item.getCount());
            productMessagingService.sendSaleMessage(productSaleMessage);
        }
        //
        orderEntity.setPayTime(DateTimeUtil.getTimestamp());
        return orderMapper.updatePay(orderEntity);
    }
}
