package com.xmall.xmall.exception;

import com.xmall.xmall.utils.StatusEnum;
import lombok.Getter;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 10:41
 * Version V1.0
 */
@Getter
public class BadRequestException extends NormalException{
    StatusEnum status = StatusEnum.BAD_REQUEST;

    public BadRequestException(String msg) {
        super(msg);
    }

    public BadRequestException(String msg, Throwable cause) {
        super(msg, cause);
    }
}
