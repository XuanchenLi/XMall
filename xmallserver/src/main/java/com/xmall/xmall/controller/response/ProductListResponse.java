package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.ProductEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/14 下午 1:25
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ProductListResponse extends NormalResponse{
    List<ProductEntity> productEntityList;
}
