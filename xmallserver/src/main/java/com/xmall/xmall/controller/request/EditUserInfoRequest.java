package com.xmall.xmall.controller.request;

import lombok.AllArgsConstructor;
import lombok.Data;
import java.sql.Date;
/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/7 下午 10:03
 * Version V1.0
 */
@Data
@AllArgsConstructor
public class EditUserInfoRequest {
    private String phone;
    private String nickname;
    private boolean gender;
    private String email;
    private Date birthday;
    private String personalRemark;
}
