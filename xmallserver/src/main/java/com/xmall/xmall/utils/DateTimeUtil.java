package com.xmall.xmall.utils;

import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 10:33
 * Version V1.0
 */
public class DateTimeUtil {
    public static final String DIVIDE_LINE = "-";
    public static final String DIVIDE_COLON = ":";

    public static final long SECOND = 1000;
    public static final long MINUTE = 60 * SECOND;
    public static final long HOUR = 60 * MINUTE;
    public static final long DAY = 24 * HOUR;
    public static final long WEEK = 7 * DAY;
    public static final String YEARFORMAT = "yyyy";
    public static final String MONTHFORMAT = "yyyy-MM";
    public static final String SHORTFORMAT = "yyyy-MM-dd";
    public static final String SHORTFORMATNOSPIT = "yyyyMMdd";
    public static final String LONGFORMATNOSPIT = "yyyyMMddHHmmss";
    public static final String LONGFORMAT = "yyyy-MM-dd HH:mm:ss";
    public static final String SUPERLONGFORMAT = "yyyy-MM-dd HH:mm:ss sss";
    private static SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public static final int FIELD_YEAR = Calendar.YEAR;
    public static final int FIELD_MONTH = Calendar.MONTH;
    public static final int FIELD_DATE = Calendar.DATE;

    /**
     * 时间戳格式化 yyyy-MM-dd HH:mm:ss
     */
    public static String getTimestampString(java.util.Date date) {
        return sdf.format(date).toString();
    }

    /**
     * 系统当前时间戳
     */
    public static Timestamp getTimestamp(){
        java.text.SimpleDateFormat myFormat = new SimpleDateFormat(LONGFORMAT);
        long stamp = System.currentTimeMillis();
        String timestamp = myFormat.format(stamp);
        return Timestamp.valueOf(timestamp);
    }


    /**
     * 日期转时间戳
     */
    public static Timestamp getTimestamp(java.util.Date date) {
        return Timestamp.valueOf(getTimestampString(date));
    }



    /**
     * 时间格式化 yyyy-MM-dd
     */
    public static String getDate() {
        java.text.SimpleDateFormat myFormat = new SimpleDateFormat(SHORTFORMAT);
        return myFormat.format(System.currentTimeMillis());
    }

    /**
     * 时间格式化 yyyy-MM-dd
     */
    public static String getDate(java.util.Date date) {
        return getDate(date, SHORTFORMAT);
    }

    /**
     * 时间格式化 yyyy-MM-dd
     */
    public static String getDate(java.util.Date date, String format) {
        String result = null;
        try {
            java.text.SimpleDateFormat myFormat = new SimpleDateFormat(format);
            result = myFormat.format(date);
        } catch (Exception e) {
            return null;
        }
        return result;
    }

    /**
     * 时间格式化 yyyy-MM-dd HH:mm:ss
     * */
    public static String getDateTime() {
        return getDateTime(new java.util.Date());
    }

    /**
     * 时间格式化 yyyy-MM-dd HH:mm:ss
     * */
    public static String getDateTime(java.util.Date date) {
        java.text.SimpleDateFormat d = new java.text.SimpleDateFormat(LONGFORMAT);
        return d.format(date);
    }

    /**
     * 时间格式化 yyyy-MM-dd
     * */
    public static String getShortDate(java.util.Date date){
        if(date==null)
            date = new java.util.Date();
        return getDate(date, SHORTFORMAT);
    }

    /**
     * 时间格式化 yyyy-MM-dd HH:mm:ss
     * */
    public static String getLongDate(java.util.Date date){
        if(date==null)
            date = new java.util.Date();
        return getDateTime(date);
    }

    /**
     * 时间格式化 yyyy-MM-dd HH:mm:ss
     * */
    public static String getTimestampStr(){
        java.text.SimpleDateFormat myFormat = new SimpleDateFormat(LONGFORMAT);
        return myFormat.format(System.currentTimeMillis());
    }

    /**
     * 时间格式化 yyyyMMddHHmmss
     * */
    public static String getLongTime(){
        java.text.SimpleDateFormat myFormat = new SimpleDateFormat(LONGFORMATNOSPIT);
        return myFormat.format(System.currentTimeMillis());
    }

    /**
     * 时间格式化 yyyyMMddHHmmss
     * */
    public static String getLongTime(long ts){
        java.text.SimpleDateFormat myFormat = new SimpleDateFormat(LONGFORMATNOSPIT);
        return myFormat.format(ts);
    }
}
