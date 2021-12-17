package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 3:20
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class OrderItemEntity implements Serializable {
    private long id;
    private String orderSn;
    private long productId;
    private String name;
    private double currentPrice;
    private double price;
    private int count;
}
