package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.NormalResponse;
import com.xmall.xmall.controller.response.OrderItemListResponse;
import com.xmall.xmall.controller.response.OrderResponse;
import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.service.OrderService;
import com.xmall.xmall.utils.StatusEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/17 下午 3:16
 * Version V1.0
 */
@RestController
@RequestMapping("/order")
public class OrderController {
    @Autowired
    private OrderService orderService;
    @GetMapping("/id/{id}")
    OrderResponse getById(@PathVariable("id") long id)
    {
        OrderResponse orderResponse = new OrderResponse();
        try{
            orderResponse.setOrderEntity(orderService.getById(id));
            orderResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderResponse;
        }catch (Exception e)
        {
            orderResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return orderResponse;
        }
    }
    @GetMapping("/orderSn/{orderSn}")
    OrderResponse getById(@PathVariable("orderSn") String orderSn)
    {
        OrderResponse orderResponse = new OrderResponse();
        try{
            orderResponse.setOrderEntity(orderService.getBySn(orderSn));
            orderResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderResponse;
        }catch (Exception e)
        {
            orderResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return orderResponse;
        }
    }
    @GetMapping("/item/orderSn/{orderSn}")
    OrderItemListResponse getAllItemBySn(@PathVariable("orderSn") String orderSn)
    {
        OrderItemListResponse orderItemListResponse = new OrderItemListResponse();
        try{
            orderItemListResponse.setOrderItemEntityList(orderService.getAllItemBySn(orderSn));
            orderItemListResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderItemListResponse;
        }catch (Exception e)
        {
            orderItemListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return orderItemListResponse;
        }
    }
}
