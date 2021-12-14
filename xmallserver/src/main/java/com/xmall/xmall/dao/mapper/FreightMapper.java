package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.FreightEntity;

import java.util.List;

public interface FreightMapper {
    List<FreightEntity> findAll() throws Exception;
    int saveFreight(FreightEntity freightEntity) throws Exception;
    int deleteById(long id) throws Exception;
}
