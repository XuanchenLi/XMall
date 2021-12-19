package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.sql.Timestamp;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/20 上午 12:24
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CommentEntity implements Serializable {
    private long id;
    private long productId;
    private String userNickname;
    private String userPhone;
    private int status;
    private Timestamp creatTime;
    private String content;
}
