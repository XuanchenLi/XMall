package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.*;
import com.xmall.xmall.dao.entity.OrderEntity;
import com.xmall.xmall.dao.entity.OrderItemEntity;
import com.xmall.xmall.service.OrderService;
import com.xmall.xmall.utils.StatusEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

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
    OrderResponse getByOrderSn(@PathVariable("orderSn") String orderSn)
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
    @GetMapping("/status/{status}")
    OrderListResponse getByStatus(@PathVariable("status") int status)
    {
        OrderListResponse orderListResponse = new OrderListResponse();
        try{
            orderListResponse.setOrderEntityList(orderService.getByStatus(status));
            orderListResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderListResponse;
        }catch (Exception e)
        {
            orderListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return orderListResponse;
        }
    }
    @GetMapping("/phone/{phone}/status/{status}")
    OrderListResponse getByStatusAndPhone(@PathVariable("status") int status, @PathVariable("phone") String phone)
    {
        OrderListResponse orderListResponse = new OrderListResponse();
        try{
            orderListResponse.setOrderEntityList(orderService.getByStatusAndPhone(status,phone));
            orderListResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderListResponse;
        }catch (Exception e)
        {
            orderListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return orderListResponse;
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
    @GetMapping("/newOrder/{phone}")
    OrderResponse allocateNewOrder(@PathVariable("phone") String phone)
    {
        OrderResponse orderResponse = new OrderResponse();
        try{
            orderResponse.setOrderEntity(orderService.newOrder(phone));
            orderResponse.setStatusCode(StatusEnum.SUCCESS);
            return orderResponse;
        }catch (Exception e)
        {
            orderResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return orderResponse;
        }
    }
    @PostMapping("/saveItem")
    NormalResponse saveItem(@RequestBody OrderItemEntity orderItemEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.saveItem(orderItemEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @PostMapping("/saveItems")
    NormalResponse saveItem(@RequestBody List<OrderItemEntity> orderItemEntityList)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.saveItems(orderItemEntityList);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @PostMapping("/calculate")
    DoubleResponse calculate(@RequestBody List<OrderItemEntity> orderItemEntityList)
    {
        DoubleResponse doubleResponse = new DoubleResponse();
        try{
            doubleResponse.setRes(orderService.calculate(orderItemEntityList));
            doubleResponse.setStatusCode(StatusEnum.SUCCESS);
            return doubleResponse;
        }catch (Exception e)
        {
            doubleResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return doubleResponse;
        }
    }
    @PostMapping("/update")
    NormalResponse update(@RequestBody OrderEntity orderEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.updateOrder(orderEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @PostMapping("/pay")
    NormalResponse pay(@RequestBody OrderEntity orderEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.pay(orderEntity);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/recv/id/{id}")
    NormalResponse recv(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.updateRecvById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/delivery/id/{id}")
    NormalResponse delivery(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.updateDeliveryById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/finish/id/{id}")
    NormalResponse finish(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.updateFinishById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/die/id/{id}")
    NormalResponse dieOrder(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.dieOrder(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/refund/id/{id}")
    NormalResponse askRefund(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.updateRefundById(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/ackRefund/id/{id}")
    NormalResponse ackRefund(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.ackRefund(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }

    @GetMapping("/declineRefund/id/{id}")
    NormalResponse declineRefund(@PathVariable("id") long id)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.declineRefund(id);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
    @GetMapping("/RefundForm/orderSn/{orderSn}")
    NormalResponse getRefundForm(@PathVariable("orderSn") String orderSn)
    {
        NormalResponse normalResponse = new NormalResponse();
        try{
            orderService.getRefundFormBySn(orderSn);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return normalResponse;
        }
    }
}
