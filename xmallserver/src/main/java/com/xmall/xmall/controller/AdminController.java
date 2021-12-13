package com.xmall.xmall.controller;

import com.xmall.xmall.controller.response.AdminResponse;
import com.xmall.xmall.controller.response.RegistrationResponse;
import com.xmall.xmall.dao.entity.AdminEntity;
import com.xmall.xmall.exception.BadRequestException;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.service.AdminService;
import com.xmall.xmall.utils.FileUtil;
import com.xmall.xmall.utils.RedisUtil;
import com.xmall.xmall.utils.StatusEnum;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/13 上午 9:33
 * Version V1.0
 */
@RestController
@RequestMapping("/admin")
public class AdminController {
    @Autowired
    private AdminService adminService;
    @Autowired
    private RedisUtil redisUtil;


    @GetMapping("/phone/{phone}")
    AdminResponse getEntityByPhone(@PathVariable("phone") String phone){
        AdminResponse adminResponse = new AdminResponse();
        AdminEntity adminEntity = new AdminEntity();
        try{
            adminEntity= adminService.getByPhone(phone);
        }catch (NotFoundException e)
        {
            adminResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return adminResponse;
        }
        adminResponse.setStatusCode(StatusEnum.SUCCESS);
        adminResponse.setAdminEntity(adminEntity);
        return adminResponse;
    }
    @PostMapping("/register")
    RegistrationResponse register(@RequestBody AdminEntity adminEntity){

        if(adminService.register(adminEntity) == -1)
        {
            return new RegistrationResponse(StatusEnum.BAD_REQUEST);
        }
        return new RegistrationResponse(StatusEnum.SUCCESS);
    }
}
