package com.xmall.xmall.controller.response;

import ch.qos.logback.core.status.StatusUtil;
import com.xmall.xmall.utils.StatusEnum;
import lombok.AllArgsConstructor;
import lombok.Data;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 10:47
 * Version V1.0
 */
@Data
@AllArgsConstructor
public class RegistrationResponse {
    private StatusEnum statusCode;
}
