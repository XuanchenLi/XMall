package com.xmall.xmall.controller.response;

import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.utils.StatusEnum;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/7 下午 10:09
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class UserInfoEntityResponse extends NormalResponse{
    UserInfoEntity userInfoEntity;
}
