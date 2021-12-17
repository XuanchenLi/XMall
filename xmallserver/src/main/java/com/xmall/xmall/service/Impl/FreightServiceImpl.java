package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.FreightEntity;
import com.xmall.xmall.dao.mapper.FreightMapper;
import com.xmall.xmall.dao.mapper.ProductMapper;
import com.xmall.xmall.service.FreightService;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.RedisUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/14 下午 2:39
 * Version V1.0
 */
@Service
@Slf4j
public class FreightServiceImpl implements FreightService {
    @Resource
    private FreightMapper freightMapper;
    @Autowired
    private RedisUtil redisUtil;

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'FREIGHT_'", unless = "#result == null")
    public List<FreightEntity> getAll() throws Exception {
        return freightMapper.findAll();
    }

    @Override
    public int saveFreight(FreightEntity freightEntity) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::FREIGHT_");
        return freightMapper.saveFreight(freightEntity);
    }

    @Override
    public int deleteById(long id) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::FREIGHT_");
        return freightMapper.deleteById(id);
    }

    @Override
    public FreightEntity getById(long id) throws Exception {
        return freightMapper.findById(id)
                .orElseThrow(() -> new Exception("找不到"));
    }
}
