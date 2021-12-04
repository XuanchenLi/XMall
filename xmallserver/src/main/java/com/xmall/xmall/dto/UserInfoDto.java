package com.xmall.xmall.dto;

import lombok.Data;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 12:17
 * Version V1.0
 */
@Data
public class UserInfoDto implements Serializable {
    private String nickname;
    private String phone;
    private String password;
    private String email;
}
