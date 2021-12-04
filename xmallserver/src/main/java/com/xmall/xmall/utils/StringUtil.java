package com.xmall.xmall.utils;

import java.util.UUID;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 10:31
 * Version V1.0
 */
public class StringUtil {
    public static String allocateUuid() {
        return UUID.randomUUID().toString().replace("-", "");
    }
}
