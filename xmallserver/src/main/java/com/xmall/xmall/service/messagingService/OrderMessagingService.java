package com.xmall.xmall.service.messagingService;

import com.xmall.xmall.dao.entity.OrderRefundFormEntity;
import com.xmall.xmall.message.UserInfoMessage;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/20 下午 5:18
 * Version V1.0
 */
@Component
public class OrderMessagingService {
    @Autowired
    RabbitTemplate rabbitTemplate;
    public void sendNewRefundMessage(OrderRefundFormEntity msg) {
        rabbitTemplate.convertAndSend("xmall.order", "newRefund", msg);
    }
}
