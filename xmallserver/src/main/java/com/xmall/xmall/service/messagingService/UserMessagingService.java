package com.xmall.xmall.service.messagingService;

import com.xmall.xmall.message.UserInfoMessage;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 9:05
 * Version V1.0
 */
@Component
public class UserMessagingService {
    @Autowired
    RabbitTemplate rabbitTemplate;

    public void sendRegistrationMessage(UserInfoMessage msg) {
        rabbitTemplate.convertAndSend("xmall.user.registration", "", msg);
    }
}
