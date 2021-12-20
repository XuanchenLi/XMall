package com.xmall.xmall.service.messageListener;

import com.xmall.xmall.message.ProductSaleMessage;
import com.xmall.xmall.message.UserInfoMessage;
import com.xmall.xmall.service.ProductService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.amqp.rabbit.annotation.Exchange;
import org.springframework.amqp.rabbit.annotation.Queue;
import org.springframework.amqp.rabbit.annotation.QueueBinding;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/19 下午 10:41
 * Version V1.0
 */
@Slf4j
@Component
public class ProductMessageListener {
    static final String PRODUCT_SALE_QUEUE = "ProductSaleQueue";

    @Autowired
    private ProductService productService;

    @RabbitListener(queues = PRODUCT_SALE_QUEUE,concurrency = "10", ackMode = "AUTO")
    public void onMessageFromSale(ProductSaleMessage message) throws Exception {
        productService.updateSaleById(message.getSale(), message.getProductId());
    }
}
