package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.CategoryEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.exception.NotFoundException;

import java.util.List;

public interface CategoryService {
    CategoryEntity getById(long id) throws NotFoundException;
    List<CategoryEntity> getAllByLevel(int level) throws NotFoundException;
    int saveCategory(CategoryEntity categoryEntity) throws Exception;
    int deleteCategoryTreeById(long id) throws Exception;
    List<CategoryEntity> getAllByParent(long id) throws Exception;
}
