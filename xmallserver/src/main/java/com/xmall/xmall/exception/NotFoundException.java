package com.xmall.xmall.exception;

import com.xmall.xmall.utils.StatusEnum;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 1:07
 * Version V1.0
 */
public class NotFoundException extends NormalException{
    StatusEnum status = StatusEnum.NOT_FOUND;

    public NotFoundException(String msg) {
        super(msg);
    }
}
