package com.xmall.xmall;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;

@SpringBootApplication
@ServletComponentScan
@MapperScan("com.xmall.xmall.**.mapper")//扫描路径
public class XmallApplication {

    public static void main(String[] args) {
        SpringApplication.run(XmallApplication.class, args);
    }

}
