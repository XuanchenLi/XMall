package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.AddressEntity;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/8 下午 10:45
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class AddressListResponse extends NormalResponse{
    List<AddressEntity> addressList;
}
