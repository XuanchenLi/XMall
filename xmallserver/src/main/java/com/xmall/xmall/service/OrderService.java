package com.xmall.xmall.service;


import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;
import com.xmall.xmall.dao.entity.OrderRefundFormEntity;


import java.util.List;

public interface OrderService {
    OrderEntity getById(long Id) throws Exception;
    OrderEntity getBySn(String orderSn) throws Exception;
    List<OrderEntity> getByStatus(int status) throws  Exception;
    List<OrderEntity> getByStatusAndPhone(int status , String phone) throws  Exception;
    List<OrderItemEntity> getAllItemBySn(String orderSn) throws Exception;
    OrderEntity newOrder(String phone) throws Exception;
    int updateOrder(OrderEntity orderEntity) throws Exception;
    int saveItem(OrderItemEntity orderItemEntity) throws Exception;
    int saveItems(List<OrderItemEntity> orderItemEntityList) throws Exception;
    double calculate(List<OrderItemEntity> orderItemEntityList) throws Exception;
    int pay(OrderEntity orderEntity) throws Exception;
    int updateDeliveryById(long id) throws Exception;
    int updateRecvById(long id) throws Exception;
    int updateFinishById(long id) throws Exception;
    int updateRefundById(long id) throws Exception;
    int saveRefundForm(OrderRefundFormEntity orderRefundFormEntity) throws Exception;
    OrderRefundFormEntity getRefundFormBySn(String orderSn) throws Exception;
    int ackRefund(long id) throws  Exception;
    int declineRefund(long id) throws  Exception;
    int dieOrder(long id)throws Exception;
}
