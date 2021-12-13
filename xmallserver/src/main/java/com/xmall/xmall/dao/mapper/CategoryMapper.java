package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.CategoryEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;

import java.util.List;
import java.util.Optional;

public interface CategoryMapper {
    Optional<CategoryEntity> findById(long id);
    List<CategoryEntity> findAllByLevel(int level);
    int saveCategory(CategoryEntity categoryEntity) throws Exception;
    int deleteCategoryById(long id) throws Exception;
    List<CategoryEntity> findAllByParent(long id) throws  Exception;
    boolean updateById(long id, CategoryEntity categoryEntity) throws Exception;
}
