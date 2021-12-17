package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.ProductEntity;

import java.util.List;
import java.util.Optional;

public interface ProductMapper {
    int saveProduct(ProductEntity productEntity) throws Exception;
    List<ProductEntity> findAllByStatus(int status) throws Exception;
    List<ProductEntity> findAllByCategory(int id) throws Exception;
    List<ProductEntity> getTenByRandom() throws Exception;
    Optional<ProductEntity> findById(long id);
    int updateSmallPicById(String path, long id)throws Exception;
    int updateBigPicById(String path, long id)throws Exception;
    int updateStatusById(int status, long id) throws  Exception;
    int updatePriceById(double price, long id) throws  Exception;
    int updateById(ProductEntity productEntity) throws  Exception;
}
