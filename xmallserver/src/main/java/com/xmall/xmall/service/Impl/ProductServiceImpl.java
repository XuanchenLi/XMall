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
    public int creatNewProduct(ProductEntity productEntity) throws Exception {
        //
        redisUtil.remove("*PRODUCT_*");
        productEntity.setSale(0);
        productEntity.setCreatTime(DateTimeUtil.getTimestamp());
        try{
            return productMapper.saveProduct(productEntity);
        }catch (Exception e)
        {
            return 0;
        }
    }

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'PRODUCT_Status_'+#status", unless = "#result == null")
    public List<ProductEntity> getAllByStatus(int status) throws Exception {
        return productMapper.findAllByStatus(status);
    }

    @Override
    public ProductEntity getById(long id) throws NotFoundException {
        return productMapper.findById(id)
                .orElseThrow(() -> new NotFoundException("商品不存在"));
    }

    @Override
    public int updateSmallPicById(String path, long id) throws NotFoundException, Exception {
        return productMapper.updateSmallPicById(path, id);
    }

    @Override
    public int updateBigPicById(String path, long id) throws NotFoundException, Exception {
        return productMapper.updateBigPicById(path, id);
    }

    @Override
    public int updateStatusById(int status, long id) throws Exception {
        redisUtil.remove("*PRODUCT_Status_" + status);
        return productMapper.updateStatusById(status, id);
    }

    @Override
    public int updatePriceById(double price, long id) throws Exception {
        return productMapper.updatePriceById(price, id);
    }

    @Override
    public int updateById(ProductEntity productEntity) throws Exception {
        return productMapper.updateById(productEntity);
    }

    @Override
    public List<ProductEntity> getTenByRandom() throws Exception {
        return productMapper.getTenByRandom();
    }
}
