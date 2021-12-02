package com.xmall.xmall.service.messageListener;

import com.xmall.xmall.message.UserInfoMessage;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/2 下午 9:23
 * Version V1.0
 */
@Slf4j
@Component
public class UserMessageListener {
    static final String USER_LOG_QUEUE = "UserLogQueue";

    @RabbitListener(queues = USER_LOG_QUEUE)
    public void onMessageFromUserLogQueue(UserInfoMessage message) throws Exception {
        log.info("queue {} received registration message: {}", USER_LOG_QUEUE, message);
    }
}
