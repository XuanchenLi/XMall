package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.CategoryEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 11:41
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CategoryListResponse extends NormalResponse{
    List<CategoryEntity> categoryEntityList;
}
