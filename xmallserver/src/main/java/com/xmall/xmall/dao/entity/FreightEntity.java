package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/14 下午 2:37
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class FreightEntity implements Serializable {
    private long id;
    private double price;
}
