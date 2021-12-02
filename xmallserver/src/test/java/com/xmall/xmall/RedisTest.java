package com.xmall.xmall;

import com.alibaba.fastjson.JSON;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.RedisUtil;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 下午 7:20
 * Version V1.0
 */
@RunWith(SpringRunner.class)
@SpringBootTest
public class RedisTest  {

    @Autowired
    RedisTemplate redisTemplate;
    @Autowired
    RedisUtil redisUtil;
    @Test
    public void testValue(){
        redisUtil.set("name","学习Redis鸭！");
        System.out.println(redisUtil.get("name"));
    }
    @Test
    public void testList() throws JsonProcessingException {
        List<Integer> s = null;
        String usersJson = new ObjectMapper().writeValueAsString(s);
        redisUtil.set("test_list", usersJson, Constants.CACHE_1MIN);
        List<Integer> usersList= JSON.parseArray((String) redisUtil.get("test_list"),Integer.class);
        System.out.println(usersList);
    }

}