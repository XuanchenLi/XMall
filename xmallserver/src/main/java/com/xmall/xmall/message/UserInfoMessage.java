package com.xmall.xmall.message;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 9:35
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class UserInfoMessage {
    public String uuid;
    public String nickName;
    public long timestamp;
}
