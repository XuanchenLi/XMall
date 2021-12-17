package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.NormalResponse;
import com.xmall.xmall.controller.response.ProductListResponse;
import com.xmall.xmall.controller.response.ProductResponse;
import com.xmall.xmall.dao.entity.ProductEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.ProductService;
import com.xmall.xmall.utils.FileUtil;
import com.xmall.xmall.utils.StatusEnum;
import com.xmall.xmall.utils.StringUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/10 下午 6:56
 * Version V1.0
 */
@RestController
@RequestMapping("/product")
public class ProductController {
    @Autowired
    private ProductService productService;
    @Autowired
    private FileUtil fileUtil;

    @PostMapping("/add")
    ProductResponse addNewProduct(@RequestBody ProductEntity productEntity)
    {
        ProductResponse productResponse = new ProductResponse();
        try{
            productResponse.setProductEntity(productService.creatNewProduct(productEntity));
            productResponse.setStatusCode(StatusEnum.SUCCESS);
            return productResponse;
        }catch (Exception e)
        {
            productResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return productResponse;
        }
    }
    @GetMapping("/status/{status}")
    ProductListResponse getAllByStatus(@PathVariable("status") int status)
    {
        ProductListResponse productListResponse = new ProductListResponse();
        productListResponse.setProductEntityList(null);
        try{
            productListResponse.setProductEntityList(productService.getAllByStatus(status));
            productListResponse.setStatusCode(StatusEnum.SUCCESS);
            return productListResponse;
        }catch (Exception e)
        {
            productListResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return productListResponse;
        }
    }
    @GetMapping("/id/{id}")
    ProductResponse getById(@PathVariable("id") long id)
    {
        ProductResponse productResponse = new ProductResponse();
        productResponse.setProductEntity(null);
        try{
            productResponse.setProductEntity(productService.getById(id));
            productResponse.setStatusCode(StatusEnum.SUCCESS);
            return productResponse;
        }catch (Exception e)
        {
            productResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return productResponse;
        }
    }

    @GetMapping("/category/{id}")
    ProductListResponse getAllByCategory(@PathVariable("id") int id)
    {
        ProductListResponse productListResponse = new ProductListResponse();
        productListResponse.setProductEntityList(null);
        try{
            productListResponse.setProductEntityList(productService.getAllByCategory(id));
            productListResponse.setStatusCode(StatusEnum.SUCCESS);
            return productListResponse;
        }catch (Exception e)
        {
            productListResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return productListResponse;
        }
    }

    @PostMapping("/id/{id}/uploadSmallPic")
    ProductResponse uploadSmallPic(@RequestParam("file") MultipartFile file, @PathVariable long id) {
        ProductResponse productResponse = new ProductResponse();
        try{
            String path = fileUtil.uploadFile(file, fileUtil.PRODUCT_SMALL_PATH);
            //更新数据库
            ProductEntity oldProductEntity = productService.getById(id);
            oldProductEntity.setSmallPicAddress(path);
            productService.updateSmallPicById(path, id);
            productResponse.setProductEntity(oldProductEntity);
            productResponse.setStatusCode(StatusEnum.SUCCESS);
            return productResponse;
        }catch (NotFoundException e)
        {
            productResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return productResponse;
        }catch (Exception e)
        {
            productResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return productResponse;
        }
    }

    @PostMapping("/id/{id}/uploadBigPic")
    ProductResponse uploadBigPic(@RequestParam("file") MultipartFile file, @PathVariable long id) {
        ProductResponse productResponse = new ProductResponse();
        try{
            String path = fileUtil.uploadFile(file, fileUtil.PRODUCT_BIG_PATH);
            //更新数据库
            ProductEntity oldProductEntity = productService.getById(id);
            oldProductEntity.setBigPicAddress(path);
            productService.updateBigPicById(path, id);
            productResponse.setProductEntity(oldProductEntity);
            productResponse.setStatusCode(StatusEnum.SUCCESS);
            return productResponse;
        }catch (NotFoundException e)
        {
            productResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return productResponse;
        }catch (Exception e)
        {
            productResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return productResponse;
        }
    }

    @GetMapping("/id/{id}/update/status/{status}")
    NormalResponse updateStatus(@PathVariable("status") int status, @PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try
        {
            productService.updateStatusById(status, id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }

    @GetMapping("/id/{id}/update/price/{price}")
    NormalResponse updatePrice(@PathVariable("price") double price, @PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try
        {
            productService.updatePriceById(price, id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }

    @PostMapping("/updateInfo")
    NormalResponse updateProductInfo(@RequestBody ProductEntity productEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        try
        {
            productService.updateById(productEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }

    @GetMapping("/random/ten")
    ProductListResponse getTenByRandom()
    {
        ProductListResponse productListResponse = new ProductListResponse();
        productListResponse.setProductEntityList(null);
        try{
            productListResponse.setProductEntityList(productService.getTenByRandom());
            productListResponse.setStatusCode(StatusEnum.SUCCESS);
            return productListResponse;
        }catch (Exception e)
        {
            productListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return productListResponse;
        }
    }


}
