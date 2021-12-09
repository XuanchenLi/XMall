package com.xmall.xmall.controller.response;

import com.xmall.xmall.utils.StatusEnum;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/8 下午 1:48
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class NormalResponse {
    public StatusEnum statusCode;
}
