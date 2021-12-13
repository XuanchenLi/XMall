package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.CategoryListResponse;
import com.xmall.xmall.controller.response.CategoryResponse;
import com.xmall.xmall.controller.response.NormalResponse;
import com.xmall.xmall.dao.entity.CategoryEntity;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.CategoryService;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StatusEnum;
import org.elasticsearch.env.NodeEnvironment;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 11:18
 * Version V1.0
 */
@RestController
@RequestMapping("/category")
public class CategoryController {
    @Autowired
    private CategoryService categoryService;

    @Autowired
    private RedisUtil redisUtil;
    @GetMapping("/id/{id}")
    CategoryResponse getById(@PathVariable("id") long id){
        CategoryResponse categoryResponse = new CategoryResponse();
        CategoryEntity categoryEntity = new CategoryEntity();
        try{
            categoryEntity= categoryService.getById(id);
        }catch (NotFoundException e)
        {
            categoryResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return categoryResponse;
        }
        categoryResponse.setStatusCode(StatusEnum.SUCCESS);
        categoryResponse.setCategoryEntity(categoryEntity);
        return categoryResponse;
    }
    @GetMapping("/level/{level}")
    CategoryListResponse getAllByLevel(@PathVariable("level") int level)
    {
        CategoryListResponse categoryListResponse = new CategoryListResponse();
        categoryListResponse.setCategoryEntityList(null);
        List<CategoryEntity> categoryEntityList;
        try{
            categoryEntityList = categoryService.getAllByLevel(level);
            categoryListResponse.setCategoryEntityList(categoryEntityList);
            categoryListResponse.setStatusCode(StatusEnum.SUCCESS);
        }catch (Exception e)
        {
            categoryListResponse.setStatusCode(StatusEnum.NOT_FOUND);
        }
        return categoryListResponse;
    }
    @PostMapping("/insert")
    NormalResponse insertCategory(@RequestBody CategoryEntity categoryEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        try {
            categoryService.saveCategory(categoryEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
        return normalResponse;
    }

    @GetMapping("/delete/id/{id}")
    NormalResponse deleteCategoryTreeById(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            categoryService.deleteCategoryTreeById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
}
