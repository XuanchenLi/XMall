package com.xmall.xmall.message;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/19 下午 10:42
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class ProductSaleMessage {
    private long productId;
    private long sale;
}
