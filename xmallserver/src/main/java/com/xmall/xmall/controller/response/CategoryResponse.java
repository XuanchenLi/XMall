package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.CategoryEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 11:24
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CategoryResponse extends NormalResponse {
    CategoryEntity categoryEntity;
}
