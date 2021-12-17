package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/16 上午 9:41
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CartEntity implements Serializable {
    private long id;
    private String userPhone;
    private long productId;
    private int count;
    private boolean del;
    private boolean checked;
}
