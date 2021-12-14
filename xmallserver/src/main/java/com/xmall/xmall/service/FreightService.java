package com.xmall.xmall.service;

import com.xmall.xmall.dao.entity.FreightEntity;

import java.util.List;

public interface FreightService {
    List<FreightEntity> getAll() throws Exception;
    int saveFreight(FreightEntity freightEntity) throws Exception;
    int deleteById(long id)throws Exception;
}
