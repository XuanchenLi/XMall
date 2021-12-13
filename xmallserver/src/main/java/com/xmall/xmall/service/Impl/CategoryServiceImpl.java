package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.CategoryEntity;
import com.xmall.xmall.dao.mapper.AdminMapper;
import com.xmall.xmall.dao.mapper.CategoryMapper;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.CategoryService;
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
 * @Date:2021/12/13 上午 11:19
 * Version V1.0
 */
@Service
@Slf4j
public class CategoryServiceImpl implements CategoryService {
    @Resource
    private CategoryMapper categoryMapper;
    @Autowired
    private RedisUtil redisUtil;

    @Override
    public CategoryEntity getById(long id) throws NotFoundException {
        return categoryMapper.findById(id)
                .orElseThrow(() -> new NotFoundException("用户不存在"));
    }

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'CATEGORY_Level_'+#level", unless = "#result == null")
    public List<CategoryEntity> getAllByLevel(int level) throws NotFoundException {
        return categoryMapper.findAllByLevel(level);
    }

    @Override
    public int saveCategory(CategoryEntity categoryEntity)throws Exception{
        //清除缓存
        redisUtil.remove("THIRTY_MINUTES::CATEGORY_Level_" + categoryEntity.getLevel());
        categoryEntity.setLeaf(true);
        try {
            CategoryEntity root = getById(categoryEntity.getParentId());
            if(root!=null && root.isLeaf())
            {
                root.setLeaf(false);
                categoryMapper.updateById(root.getId(), root);
            }
            return categoryMapper.saveCategory(categoryEntity);
        }catch (NotFoundException e)
        {
            return categoryMapper.saveCategory(categoryEntity);
        }

    }

    @Override
    @Cacheable(cacheNames = Constants.THIRTY_MINUTES, key ="'CATEGORY_Parent_'+#id", unless = "#result == null")
    public List<CategoryEntity> getAllByParent(long id) throws Exception {
        return categoryMapper.findAllByParent(id);
    }

    @Override
    public int deleteCategoryTreeById(long id) throws Exception {
        //清除缓存
        CategoryEntity root = getById(id);
        if(root == null) return 0;
        int count = 0;
        redisUtil.remove("THIRTY_MINUTES::CATEGORY_Parent_" + id);
        redisUtil.remove("THIRTY_MINUTES::CATEGORY_Level_" + root.getLevel());
        redisUtil.remove("THIRTY_MINUTES::CATEGORY_Level_" + root.getLevel() + 1);
        if(!root.isLeaf())
        {//非叶子节点
            List<CategoryEntity> sons = getAllByParent(id);
            for (CategoryEntity entity: sons)//删除儿子
            {
                if(entity.isLeaf())
                {
                    count += categoryMapper.deleteCategoryById(entity.getId());
                }
                else {
                    count += deleteCategoryTreeById(entity.getId());//递归
                }
            }
        }
        count += categoryMapper.deleteCategoryById(id);
        if(root.getParentId() != 0)//不是根节点
        {
            List<CategoryEntity> brothers = getAllByParent(root.getParentId());
            if(brothers.isEmpty())//更新根节点
            {
                CategoryEntity father = getById(root.getParentId());
                father.setLeaf(true);
                categoryMapper.updateById(father.getId(), father);
            }
        }
        return count;
    }
}
