package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.FreightEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/16 下午 8:07
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class FreightResponse extends NormalResponse{
    FreightEntity freightEntity;
}
