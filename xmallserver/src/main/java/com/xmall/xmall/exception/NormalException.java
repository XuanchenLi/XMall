package com.xmall.xmall.exception;

import com.xmall.xmall.utils.StatusEnum;
import lombok.Getter;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 1:00
 * Version V1.0
 */
@Getter
public class NormalException extends Exception {
    StatusEnum status= StatusEnum.SUCCESS;
    public NormalException(String msg)
    {
        super(msg);
    }
    public NormalException(String msg, Throwable cause)
    {
        super(msg, cause);
    }
}
