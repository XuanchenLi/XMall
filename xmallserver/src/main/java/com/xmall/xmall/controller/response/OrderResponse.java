package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.OrderEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 3:08
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class OrderResponse extends NormalResponse{
    OrderEntity orderEntity;
}
