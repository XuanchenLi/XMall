package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.ProductEntity;
import com.xmall.xmall.exception.NotFoundException;

import java.util.List;

public interface ProductService {
    ProductEntity creatNewProduct(ProductEntity productEntity) throws Exception;
    List<ProductEntity> getAllByStatus (int status) throws Exception;
    List<ProductEntity> getAllByCategory (int id) throws Exception;
    List<ProductEntity> getFiveByRandom () throws Exception;
    ProductEntity getById(long id) throws NotFoundException;
    int updateSmallPicById(String path, long id) throws NotFoundException, Exception;
    int updateBigPicById(String path, long id) throws NotFoundException, Exception;
    int updateStatusById(int status, long id) throws Exception;
    int updatePriceById(double price, long id) throws Exception;
    int updateById(ProductEntity productEntity) throws Exception;
    int updateStorageById(long storage, long id) throws Exception;
    int updateSaleById(long sale, long id) throws Exception;
}
