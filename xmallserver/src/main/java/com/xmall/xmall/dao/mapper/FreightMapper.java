package com.xmall.xmall.dao.mapper;

import com.xmall.xmall.dao.entity.FreightEntity;

import javax.swing.text.html.Option;
import java.util.List;
import java.util.Optional;

public interface FreightMapper {
    List<FreightEntity> findAll() throws Exception;
    int saveFreight(FreightEntity freightEntity) throws Exception;
    int deleteById(long id) throws Exception;
    Optional<FreightEntity> findById(long id) throws Exception;
}
