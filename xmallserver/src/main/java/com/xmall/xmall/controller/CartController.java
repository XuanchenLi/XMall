package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.CartListResponse;
import com.xmall.xmall.controller.response.CartResponse;
import com.xmall.xmall.controller.response.DoubleResponse;
import com.xmall.xmall.controller.response.NormalResponse;
import com.xmall.xmall.dao.entity.CartEntity;
import com.xmall.xmall.service.CartService;
import com.xmall.xmall.utils.StatusEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/16 上午 9:40
 * Version V1.0
 */
@RestController
@RequestMapping("/cart")
public class CartController {
    @Autowired
    private CartService cartService;

    @GetMapping("/phone/{phone}")
    CartListResponse getAllActiveByPhone(@PathVariable("phone") String phone)
    {
        CartListResponse cartListResponse = new CartListResponse();
        try{
            cartListResponse.setCartEntityList(cartService.getAllActiveByPhone(phone));
            cartListResponse.setStatusCode(StatusEnum.SUCCESS);
            return cartListResponse;
        }catch (Exception e)
        {
            cartListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return cartListResponse;
        }
    }
    @GetMapping("/delete/phone/{phone}/id/{id}")
    CartResponse lazyDeleteById(@PathVariable("id") long id, @PathVariable("phone") String phone)
    {
        CartResponse cartResponse = new CartResponse();
        try{
            CartEntity cartEntity = cartService.getById(id);
            cartService.lazyDeleteById(id, phone);
            cartEntity.setDel(true);
            cartResponse.setCartEntity(cartEntity);
            cartResponse.setStatusCode(StatusEnum.SUCCESS);
            return cartResponse;
        }catch (Exception e)
        {
            cartResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return cartResponse;
        }
    }
    @GetMapping("/check/phone/{phone}/id/{id}")
    NormalResponse checkById (@PathVariable("id") long id, @PathVariable("phone") String phone)
    {
        NormalResponse normalResponse = new NormalResponse();
        try {
            cartService.checkById(id, phone);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return normalResponse;
        }
    }
    @GetMapping("/disCheck/phone/{phone}/id/{id}")
    NormalResponse discheckById (@PathVariable("id") long id, @PathVariable("phone") String phone)
    {
        NormalResponse normalResponse = new NormalResponse();
        try {
            cartService.disCheckById(id, phone);
            normalResponse.setStatusCode(StatusEnum.SUCCESS);
            return normalResponse;
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return normalResponse;
        }
    }
    @PostMapping("/updateCount")
    CartResponse updateCountById(@RequestBody CartEntity cartEntity)
    {
        CartResponse cartResponse = new CartResponse();
        try{
            int count = cartService.updateCountById(cartEntity);
            cartEntity.setCount(count);
            cartResponse.setCartEntity(cartEntity);
            cartResponse.setStatusCode(StatusEnum.SUCCESS);
            return cartResponse;
        }catch (Exception e)
        {
            cartResponse.setCartEntity(cartEntity);
            cartResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return cartResponse;
        }
    }
    @PostMapping("/add")
    CartResponse addCart(@RequestBody CartEntity cartEntity)
    {
        CartResponse cartResponse = new CartResponse();
        try{
            cartEntity.setChecked(true);
            cartService.insertCart(cartEntity);
            cartResponse.setCartEntity(cartEntity);
            cartResponse.setStatusCode(StatusEnum.SUCCESS);
            return cartResponse;
        }catch (Exception e)
        {
            cartResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return cartResponse;
        }
    }

    @PostMapping("/calculate")
    DoubleResponse calculate(@RequestBody List<CartEntity> cartEntityList)
    {
        DoubleResponse doubleResponse = new DoubleResponse();
        try{
            doubleResponse.setRes(cartService.calculate(cartEntityList));
            doubleResponse.setStatusCode(StatusEnum.SUCCESS);
            return doubleResponse;
        }catch (Exception e)
        {
            doubleResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
            return doubleResponse;
        }
    }
}
