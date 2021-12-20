package com.xmall.xmall.dao.mapper;

import com.sun.org.apache.xalan.internal.lib.ExsltCommon;
import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;
import com.xmall.xmall.dao.entity.OrderRefundFormEntity;

import java.sql.Timestamp;
import java.util.List;
import java.util.Optional;

public interface OrderMapper {
    Optional<OrderEntity> findById(long id) throws Exception;
    Optional<OrderEntity> findBySn(String orderSn) throws Exception;
    List<OrderEntity> findByStatus(int status) throws Exception;
    List<OrderEntity> findByStatusAndPhone(int status,String phone) throws Exception;
    int updateOrder(OrderEntity orderEntity) throws  Exception;
    int saveOrder(OrderEntity orderEntity) throws  Exception;
    int updatePay(OrderEntity orderEntity)throws  Exception;
    int updateDelivery(OrderEntity orderEntity) throws Exception;
    int updateRecv(OrderEntity orderEntity) throws Exception;
    int updateRefund(OrderEntity orderEntity) throws Exception;
    int updateFinish(OrderEntity orderEntity) throws Exception;
    int saveOrderItem(OrderItemEntity orderItemEntity) throws Exception;
    int saveRefundForm(OrderRefundFormEntity orderRefundFormEntity) throws  Exception;
    int updateRefundFormHandle(OrderRefundFormEntity orderRefundFormEntity) throws  Exception;
    List<OrderItemEntity> findAllItemBySn(String orderSn) throws Exception;
    OrderRefundFormEntity findFormBySn(String orderSn) throws Exception;

}
