package com.xmall.xmall.service.Impl;

import com.sun.org.apache.xpath.internal.operations.Or;
import com.xmall.xmall.dao.entity.*;
import com.xmall.xmall.dao.mapper.OrderMapper;
import com.xmall.xmall.dao.mapper.ProductMapper;
import com.xmall.xmall.message.ProductSaleMessage;
import com.xmall.xmall.service.OrderService;
import com.xmall.xmall.service.ProductService;
import com.xmall.xmall.service.messagingService.OrderMessagingService;
import com.xmall.xmall.service.messagingService.ProductMessagingService;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StringUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.sql.Timestamp;
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
    @Autowired
    private OrderMessagingService orderMessagingService;
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
    public List<OrderEntity> getByStatus(int status) throws Exception {
        return orderMapper.findByStatus(status);
    }

    @Override
    public List<OrderEntity> getByStatusAndPhone(int status, String phone) throws Exception {

        return orderMapper.findByStatusAndPhone(status,phone);
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
                log.info(""+item.getCount());
                throw new Exception("超限");
            }
            productEntityList.add(oldProduct);
        }
        int res = 0, i =0;
        for (OrderItemEntity item : orderItemEntityList)
        {
            productService.updateStorageById(productEntityList.get(i).getStorage() - item.getCount(), productEntityList.get(i).getId());
            if (productEntityList.get(i).getStorage() == item.getCount())
            {
                productService.updateStatusById(3, productEntityList.get(i).getId());
            }
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
        OrderEntity oldOrderEntity = getById(orderEntity.getId());
        if(oldOrderEntity.getStatus() != 0) throw new Exception("重复支付");
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

    @Override
    public int updateDeliveryById(long id) throws Exception {
        OrderEntity orderEntity = getById(id);
        if(orderEntity.getStatus() != 1) throw new Exception("重复操作");
        orderEntity.setDeliveryTime(DateTimeUtil.getTimestamp());
        return orderMapper.updateDelivery(orderEntity);
    }

    @Override
    public int updateRecvById(long id) throws Exception {
        OrderEntity orderEntity = getById(id);
        if(orderEntity.getStatus() != 2) throw new Exception("重复操作");
        orderEntity.setRecvTime(DateTimeUtil.getTimestamp());
        return orderMapper.updateRecv(orderEntity);
    }

    @Override
    public int updateFinishById(long id) throws Exception {
        OrderEntity orderEntity = getById(id);
        if(orderEntity.getStatus() == 3) throw new Exception("重复操作");
        orderEntity.setDieTime(DateTimeUtil.getTimestamp());
        return orderMapper.updateFinish(orderEntity);
    }

    @Override
    public int updateRefundById(long id) throws Exception {
        OrderRefundFormEntity orderRefundFormEntity = new OrderRefundFormEntity();
        OrderEntity orderEntity = getById(id);
        orderRefundFormEntity.setCreatTime(DateTimeUtil.getTimestamp());
        orderRefundFormEntity.setOrderSn(orderEntity.getOrderSn());
        orderRefundFormEntity.setRefundPrice(orderEntity.getPayPrice());
        orderRefundFormEntity.setUserPhone(orderEntity.getUserPhone());
        orderRefundFormEntity.setPreStatus(orderEntity.getStatus());
        orderRefundFormEntity.setStatus(0);
        orderMessagingService.sendNewRefundMessage(orderRefundFormEntity);
        orderEntity.setRefundTime(DateTimeUtil.getTimestamp());
        return orderMapper.updateRefund(orderEntity);
    }

    @Override
    public int saveRefundForm(OrderRefundFormEntity orderRefundFormEntity) throws Exception {
        return orderMapper.saveRefundForm(orderRefundFormEntity);
    }

    @Override
    public int updateOrder(OrderEntity orderEntity) throws Exception {
        return orderMapper.updateOrder(orderEntity);
    }


    @Override
    public int ackRefund(long id) throws Exception {

        OrderEntity orderEntity = getById(id);
        OrderRefundFormEntity orderRefundFormEntity = getRefundFormBySn(orderEntity.getOrderSn());
        List<OrderItemEntity> orderItemEntityList = getAllItemBySn(orderEntity.getOrderSn());
        //加库存
        for (OrderItemEntity item : orderItemEntityList)
        {
            ProductEntity oldProduct = productService.getById(item.getProductId());
            productService.updateStorageById(oldProduct.getStorage() + item.getCount(), oldProduct.getId());
        }
        //减销量
        for (OrderItemEntity item : orderItemEntityList) {
            ProductSaleMessage productSaleMessage = new ProductSaleMessage();
            productSaleMessage.setProductId(item.getProductId());
            productSaleMessage.setSale(- item.getCount());
            productMessagingService.sendSaleMessage(productSaleMessage);
        }
        //订单关闭
        updateFinishById(orderEntity.getId());
        //更新表单
        orderRefundFormEntity.setHandleTime(DateTimeUtil.getTimestamp());
        orderRefundFormEntity.setStatus(1);
        return orderMapper.updateRefundFormHandle(orderRefundFormEntity);

    }

    @Override
    public int declineRefund(long id) throws Exception {
        OrderEntity orderEntity = getById(id);
        OrderRefundFormEntity orderRefundFormEntity = getRefundFormBySn(orderEntity.getOrderSn());
        //订单还原状态
        orderEntity.setStatus(orderRefundFormEntity.getPreStatus());
        updateOrder(orderEntity);
        //更新表单
        orderRefundFormEntity.setHandleTime(DateTimeUtil.getTimestamp());
        orderRefundFormEntity.setStatus(2);
        return orderMapper.updateRefundFormHandle(orderRefundFormEntity);
    }

    @Override
    public OrderRefundFormEntity getRefundFormBySn(String orderSn) throws Exception {
        return orderMapper.findFormBySn(orderSn);
    }

    @Override
    public int dieOrder(long id) throws Exception {
        OrderEntity orderEntity = getById(id);
        List<OrderItemEntity> orderItemEntityList = getAllItemBySn(orderEntity.getOrderSn());
        //加库存
        for (OrderItemEntity item : orderItemEntityList)
        {
            ProductEntity oldProduct = productService.getById(item.getProductId());
            productService.updateStorageById(oldProduct.getStorage() + item.getCount(), oldProduct.getId());
        }
        //订单关闭
        return updateFinishById(orderEntity.getId());
    }
}
