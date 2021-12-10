package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/8 下午 10:26
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class AddressEntity implements Serializable {
    private long id;
    private String uuid;
    private String userPhone;
    private String name;
    private String phone;
    private String province;
    private String city;
    private String region;
    private String detail;
}
