package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.sql.Timestamp;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 3:08
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class OrderEntity implements Serializable {
    private long id;
    private String userPhone;
    private String orderSn;
    private double totPrice;
    private double payPrice;
    private double freightPrice;
    private double promotionPrice;
    private double couponPrice;
    private int payType;
    private int status;
    private String userAddressInfo;
    private Timestamp creatTime;
    private Timestamp payTime;
    private Timestamp deliveryTime;
    private Timestamp recvTime;
    private Timestamp commentTime;
    private Timestamp refundTime;
    private Timestamp dieTime;
}
