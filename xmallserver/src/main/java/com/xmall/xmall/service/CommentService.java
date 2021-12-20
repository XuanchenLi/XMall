package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.CommentEntity;

public interface CommentService {
    int saveComment(CommentEntity commentEntity) throws Exception;
}
