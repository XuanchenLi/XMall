package com.xmall.xmall;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.amqp.support.converter.Jackson2JsonMessageConverter;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.context.annotation.Bean;
import org.springframework.amqp.support.converter.MessageConverter;

@SpringBootApplication
@ServletComponentScan
@EnableCaching
@MapperScan("com.xmall.xmall.**.mapper")//扫描路径
public class XmallApplication {

    //将Java对象转换为RabbitMQ的消息
    @Bean
    MessageConverter createMessageConverter() {
        return new Jackson2JsonMessageConverter();
    }
    public static void main(String[] args) {
        SpringApplication.run(XmallApplication.class, args);
    }

}
