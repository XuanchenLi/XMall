package com.xmall.xmall.utils;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 下午 8:00
 * Version V1.0
 */
public class Constants {
    public static final String  ONE_MINUTE = "ONE_MINUTE";
    public static final String  PERMANENT = "PERMANENT";
    public static final String  THIRTY_MINUTES = "THIRTY_MINUTES";

    /**  1天缓存组  */
    public static final long CACHE_1DAY = 86400;
    /** 30分钟缓存组 */
    public static final long CACHE_30MINS = 1800;
    /** 1小时缓存组 */
    public static final long CACHE_1HOUR = 3600;
    /** 10秒钟缓存组 */
    public static final long CACHE_10SECOND = 10;
    /** 1分钟缓存组 */
    public static final long CACHE_1MIN= 60;

    public static final String USER_KEY_CACHE_PREFIX= "USER_";
    public static final String CATEGORY_KEY_CACHE_PREFIX= "CATEGORY_";
}
