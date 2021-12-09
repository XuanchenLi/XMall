package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

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
public class AddressEntity {
    private long id;
    private String userPhone;
    private String name;
    private String phone;
    private String province;
    private String city;
    private String region;
    private String detail;
}
