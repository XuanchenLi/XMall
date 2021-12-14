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
 * @Date:2021/12/10 下午 6:57
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ProductEntity implements Serializable {
    private long id;
    private String name;
    private String introduction;
    private double price;
    private double currentPrice;
    private String smallPicAddress;
    private String bigPicAddress;
    private int limitation;
    private long categoryId;
    private boolean isHaveAttribute;
    private long freightTemplateId;
    private int status;
    private long sale;
    private String unit;
    private long storageId;
    private Timestamp creatTime;
}
