package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.CommentEntity;

public interface CommentMapper {
    int saveComment(CommentEntity commentEntity) throws Exception;
}
