package com.xmall.xmall.dao.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 11:18
 * Version V1.0
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class CategoryEntity  implements Serializable {
    private long id;
    private long parentId;
    private String name;
    private int level;
    private boolean isLeaf;
}
