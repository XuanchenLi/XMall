package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.FreightListResponse;
import com.xmall.xmall.controller.response.FreightResponse;
import com.xmall.xmall.controller.response.NormalResponse;
import com.xmall.xmall.dao.entity.FreightEntity;
import com.xmall.xmall.service.FreightService;
import com.xmall.xmall.utils.StatusEnum;
import jdk.nashorn.internal.objects.annotations.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/14 下午 2:39
 * Version V1.0
 */
@RestController
@RequestMapping("/freight")
public class FreightController {
    @Autowired
    private FreightService freightService;

    @GetMapping("/")
    FreightListResponse getAll()
    {
        FreightListResponse freightListResponse = new FreightListResponse();
        freightListResponse.setFreightEntityList(null);
        try{
            freightListResponse.setFreightEntityList(freightService.getAll());
            freightListResponse.setStatusCode(StatusEnum.SUCCESS);
            return freightListResponse;
        }catch (Exception e)
        {
            freightListResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return freightListResponse;
        }
    }
    @GetMapping("/id/{id}")
    FreightResponse getById(@PathVariable("id") long id)
    {
        FreightResponse freightResponse = new FreightResponse();
        freightResponse.setFreightEntity(null);
        try{
            freightResponse.setFreightEntity(freightService.getById(id));
            freightResponse.setStatusCode(StatusEnum.SUCCESS);
            return freightResponse;
        }catch (Exception e)
        {
            freightResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return freightResponse;
        }
    }
    @GetMapping("/delete/id/{id}")
    NormalResponse deleteById(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            freightService.deleteById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/insert/price/{price}")
    NormalResponse deleteById(@PathVariable("price") double price)
    {
        NormalResponse normalResponse = new NormalResponse();
        FreightEntity freightEntity = new FreightEntity();
        freightEntity.setPrice(price);
        try{
            freightService.saveFreight(freightEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
}
