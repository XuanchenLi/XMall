package com.xmall.xmall.service.messageListener;

import com.xmall.xmall.dao.entity.OrderRefundFormEntity;
import com.xmall.xmall.message.ProductSaleMessage;
import com.xmall.xmall.service.OrderService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/20 下午 5:17
 * Version V1.0
 */
@Slf4j
@Component
public class OrderMessageListener {
    static final String ORDER_NEW_REFUND_QUEUE = "OrderNewRefundQueue";
    @Autowired
    private OrderService orderService;
    @RabbitListener(queues = ORDER_NEW_REFUND_QUEUE,concurrency = "5", ackMode = "AUTO")
    public void onMessageFromRefund(OrderRefundFormEntity message) throws Exception {
        orderService.saveRefundForm(message);
    }
}
