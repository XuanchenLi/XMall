package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.ProductEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/14 下午 1:56
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ProductResponse extends NormalResponse{
    ProductEntity productEntity;
}
