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
 * @Date:2021/12/13 上午 9:33
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class AdminEntity implements Serializable {
    private long id;
    private String uuid;
    private String phone;
    private String password;
    private Timestamp registerTime;
    private long settingId;
}
