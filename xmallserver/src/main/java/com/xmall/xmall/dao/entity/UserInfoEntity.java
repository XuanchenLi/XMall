package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.sql.Date;
import java.sql.Timestamp;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/11/30 下午 10:49
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class UserInfoEntity implements Serializable {

    private long id;
    private String uuid;
    private String nickname;
    private String phone;
    private String password;
    private Timestamp registerTime;
    private boolean gender;
    private String icon;
    private Date birthday;
    private String personalRemark;
    private long settingId;
}
