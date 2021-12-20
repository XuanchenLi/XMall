package com.xmall.xmall.service.Impl;

import com.xmall.xmall.dao.entity.CommentEntity;
import com.xmall.xmall.dao.mapper.CommentMapper;
import com.xmall.xmall.service.CommentService;
import com.xmall.xmall.utils.DateTimeUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/20 下午 4:52
 * Version V1.0
 */
@Service
@Slf4j
public class CommentServiceImpl implements CommentService {
    @Resource
    private CommentMapper commentMapper;

    @Override
    public int saveComment(CommentEntity commentEntity) throws Exception {
        commentEntity.setCreatTime(DateTimeUtil.getTimestamp());
        commentEntity.setStatus(1);
        return commentMapper.saveComment(commentEntity);
    }
}
