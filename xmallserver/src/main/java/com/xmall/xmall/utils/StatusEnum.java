package com.xmall.xmall.utils;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.ToString;


@Getter
public enum StatusEnum {

    SUCCESS(200, ""), // 成功
    BAD_REQUEST(400, "请求错误"),
    FORBIDDEN(403, "禁止访问"),
    NOT_FOUND(404, "未找到相关信息"),
    INTERNAL_ERROR(500, "服务器内部错误"),
    SERVICE_UNAVAILIBLE(503, "服务器暂不可用");

    private int code;
    private String message;

    StatusEnum(int code, String message)
    {
        this.code = code;
        this.message = message;
    }
}
