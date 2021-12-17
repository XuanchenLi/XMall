package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.ProductEntity;
import com.xmall.xmall.dao.mapper.ProductMapper;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.ProductService;
import com.xmall.xmall.utils.Constants;
import com.xmall.xmall.utils.DateTimeUtil;
import com.xmall.xmall.utils.RedisUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;
import java.util.Optional;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/10 下午 6:58
 * Version V1.0
 */
@Service
@Slf4j
public class ProductServiceImpl implements ProductService {
    @Resource
    private ProductMapper productMapper;
    @Autowired
    private RedisUtil redisUtil;

    @Override
    public ProductEntity creatNewProduct(ProductEntity productEntity) throws Exception {
        //
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        productEntity.setSale(0);
        productEntity.setCreatTime(DateTimeUtil.getTimestamp());
        productMapper.saveProduct(productEntity);
        return productEntity;

    }

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'PRODUCT_Status_'+#status", unless = "#result == null")
    public List<ProductEntity> getAllByStatus(int status) throws Exception {
        return productMapper.findAllByStatus(status);
    }

    @Override
    public List<ProductEntity> getAllByCategory(int id) throws Exception {
        return productMapper.findAllByCategory(id);
    }

    @Override
    public ProductEntity getById(long id) throws NotFoundException {

        return productMapper.findById(id)
                .orElseThrow(() -> new NotFoundException("商品不存在"));
    }

    @Override
    public int updateSmallPicById(String path, long id) throws NotFoundException, Exception {
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        return productMapper.updateSmallPicById(path, id);
    }

    @Override
    public int updateBigPicById(String path, long id) throws NotFoundException, Exception {
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        return productMapper.updateBigPicById(path, id);
    }

    @Override
    public int updateStatusById(int status, long id) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        return productMapper.updateStatusById(status, id);
    }

    @Override
    public int updatePriceById(double price, long id) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        return productMapper.updatePriceById(price, id);
    }

    @Override
    public int updateById(ProductEntity productEntity) throws Exception {
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_0");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_1");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_2");
        redisUtil.remove("THIRTY_MINUTES::PRODUCT_Status_3");
        return productMapper.updateById(productEntity);
    }

    @Override
    public List<ProductEntity> getTenByRandom() throws Exception {
        return productMapper.getTenByRandom();
    }
}
