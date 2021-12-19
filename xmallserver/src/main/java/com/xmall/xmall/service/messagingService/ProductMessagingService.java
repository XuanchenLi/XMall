package com.xmall.xmall.service.messagingService;

import com.xmall.xmall.message.ProductSaleMessage;
import com.xmall.xmall.message.UserInfoMessage;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/19 下午 10:41
 * Version V1.0
 */
@Component
public class ProductMessagingService {
    @Autowired
    RabbitTemplate rabbitTemplate;

    public void sendSaleMessage(ProductSaleMessage msg) {
        rabbitTemplate.convertAndSend("xmall.product", "updateSale", msg);
    }
}
