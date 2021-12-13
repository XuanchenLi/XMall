package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.AdminEntity;
import com.xmall.xmall.dao.mapper.AdminMapper;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.AdminService;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StringUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Optional;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 9:34
 * Version V1.0
 */
@Service
@Slf4j
public class AdminServiceImpl implements AdminService {
    @Resource
    private AdminMapper adminMapper;

    @Autowired
    private RedisUtil redisUtil;

    @Override
    public int register(AdminEntity adminEntity) {
        adminEntity.setRegisterTime(DateTimeUtil.getTimestamp());
        adminEntity.setUuid(StringUtil.allocateUuid());
        Optional<AdminEntity> adminInfo = adminMapper.findByPhone(adminEntity.getPhone());
        if(adminInfo.isPresent())
        {
            return -1;
        }
        try{
            return adminMapper.saveAdmin(adminEntity);
        }catch (Exception e)
        {
            return -1;
        }
    }

    @Override
    @Cacheable(cacheNames = Constants.ONE_MINUTE, key ="'ADMIN_Phone_'+#phone", unless = "#result == null")
    public AdminEntity getByPhone(String phone) throws NotFoundException {
        return adminMapper.findByPhone(phone)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }
}
