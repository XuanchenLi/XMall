package com.xmall.xmall.service.Impl;

import com.xmall.xmall.controller.response.CartResponse;
import com.xmall.xmall.dao.entity.CartEntity;
import com.xmall.xmall.dao.entity.ProductEntity;
import com.xmall.xmall.dao.mapper.CartMapper;
import com.xmall.xmall.service.CartService;
import com.xmall.xmall.service.ProductService;
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
 * @Date:2021/12/16 上午 9:42
 * Version V1.0
 */
@Service
@Slf4j
public class CartServiceImpl implements CartService {
    @Resource
    private CartMapper cartMapper;
    @Resource
    private ProductService productService;
    @Autowired
    private RedisUtil redisUtil;

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'CART_Phone_'+#phone", unless = "#result == null")
    public List<CartEntity> getAllActiveByPhone(String phone) throws Exception {
        return cartMapper.findAllActiveByPhone(phone);
    }

    @Override
    public int lazyDeleteById(long id, String phone) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::CART_Phone_" + phone);
        return cartMapper.lazyDeleteById(id);
    }

    @Override
    public int updateCountById(CartEntity cartEntity) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::CART_Phone_" + cartEntity.getUserPhone());
        ProductEntity productEntity = productService.getById(cartEntity.getProductId());
        if ( cartEntity.getCount() > productEntity.getLimitation() && productEntity.getLimitation() != -1)
        {
            cartEntity.setCount(productEntity.getLimitation());
        }
        cartMapper.updateCountById(cartEntity.getCount(), cartEntity.getId());
        return cartEntity.getCount();
    }

    @Override
    public int insertCart(CartEntity cartEntity) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::CART_Phone_" + cartEntity.getUserPhone());
        return cartMapper.saveCart(cartEntity);
    }

    @Override
    public CartEntity getById(long id) throws Exception {
        return cartMapper.findById(id);
    }

    @Override
    public double calculate(List<CartEntity> cartEntityList) throws Exception {
        double res = 0;
        for (int i = 0; i < cartEntityList.size(); ++i)
        {
            if(!cartEntityList.get( i).isDel() && cartEntityList.get(i).isChecked())
            {
                CartEntity cartEntity = cartEntityList.get(i);
                ProductEntity productEntity = productService.getById(cartEntity.getProductId());
                if(productEntity.getStatus() == 1&& (productEntity.getLimitation() >= cartEntity.getCount())
                        || productEntity.getLimitation() == -1)
                {
                    res += cartEntity.getCount() * productEntity.getCurrentPrice();
                }
                else {
                    return -1;
                }
            }
        }
        return res;
    }

    @Override
    public int checkById(long id, String phone) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::CART_Phone_" + phone);
        return cartMapper.checkById(id);
    }

    @Override
    public int disCheckById(long id, String phone) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::CART_Phone_" + phone);
        return cartMapper.disCheckById(id);
    }
}
