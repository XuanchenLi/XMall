package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.sql.Timestamp;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 4:03
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class OrderRefundFormEntity {
    private long id;
    private String orderSn;
    private Timestamp creatTime;
    private double refundPrice;
    private String userPhone;
    private Timestamp handleTime;
    private int status;
}
