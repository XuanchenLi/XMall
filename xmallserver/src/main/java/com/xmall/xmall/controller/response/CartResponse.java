package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.CartEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/16 上午 9:41
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CartResponse extends NormalResponse{
    CartEntity cartEntity;
}
