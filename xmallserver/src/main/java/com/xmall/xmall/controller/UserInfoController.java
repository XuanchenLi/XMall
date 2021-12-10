package com.xmall.xmall.controller;

import com.alibaba.fastjson.JSON;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.xmall.xmall.controller.request.EditUserInfoRequest;
import com.xmall.xmall.controller.response.*;
import com.xmall.xmall.dao.entity.AddressEntity;
import com.xmall.xmall.dao.entity.UserInfoEntity;
import com.xmall.xmall.dao.mapper.UserInfoMapper;
import com.xmall.xmall.dto.UserInfoDto;
import com.xmall.xmall.exception.BadRequestException;
import com.xmall.xmall.exception.NotFoundException;
import com.xmall.xmall.mapper.UserMapper;
import com.xmall.xmall.service.UserService;
import com.xmall.xmall.utils.*;
import org.apache.tomcat.util.http.fileupload.FileUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.core.io.ClassPathResource;
import org.springframework.core.io.Resource;
import org.springframework.util.ResourceUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/1 上午 1:21
 * Version V1.0
 */

@RestController
@RequestMapping("/user")
public class UserInfoController {
    @Autowired
    private UserService userService;
    @Autowired
    private RedisUtil redisUtil;
    @Autowired
    private FileUtil fileUtil;

    private static final  String key = "userCache_";

    @GetMapping("/")
    List<UserInfoDto> getAllUser() throws JsonProcessingException {
        List<UserInfoEntity> userInfoEntityList = null;
        if (redisUtil.exists(key + "UserList"))
        {
            userInfoEntityList = JSON.parseArray((String) redisUtil.get(key + "UserList"), UserInfoEntity.class);
        }
        if(userInfoEntityList == null) {//不在缓存中
            List<UserInfoEntity> userInfoList = userService.getAll();//从数据库获取
            if (!userInfoList.isEmpty())
            {
                String usersJson = new ObjectMapper().writeValueAsString(userInfoList);
                redisUtil.set(key + "UserList", usersJson, Constants.CACHE_30MINS);
                //redisUtil.setExpire(key + "UserList", 30, TimeUnit.MINUTES);
                return userInfoList
                        .stream()
                        .map(UserMapper.INSTANCE::userInfoEntityToDto)
                        .collect(Collectors.toList());
            }
        }
        return userInfoEntityList
                .stream()
                .map(UserMapper.INSTANCE::userInfoEntityToDto)
                .collect(Collectors.toList());
    }

    @GetMapping("/uuid/{uuid}")
    UserInfoResponse getByUuid(@PathVariable("uuid") String uuid) throws NotFoundException {
        UserInfoResponse userInfoResponse = new UserInfoResponse();
        UserInfoEntity userInfoEntity = new UserInfoEntity();
        try{
            userInfoEntity= userService.getByUuid(uuid);
        }catch (NotFoundException e)
        {
            userInfoResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return userInfoResponse;
        }
        userInfoResponse.setStatusCode(StatusEnum.SUCCESS);
        userInfoResponse.setUserInfoDto(UserMapper.INSTANCE.userInfoEntityToDto(userInfoEntity));
        return userInfoResponse;
    }

    @GetMapping("/id/{id}")
    UserInfoResponse getById(@PathVariable("id") int id) throws NotFoundException {
        UserInfoResponse userInfoResponse = new UserInfoResponse();
        UserInfoEntity userInfoEntity = new UserInfoEntity();
        try{
            userInfoEntity= userService.getById(id);
        }catch (NotFoundException e)
        {
            userInfoResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return userInfoResponse;
        }
        userInfoResponse.setStatusCode(StatusEnum.SUCCESS);
        userInfoResponse.setUserInfoDto(UserMapper.INSTANCE.userInfoEntityToDto(userInfoEntity));
        return userInfoResponse;
    }
    @GetMapping("/phone/{phone}")
    UserInfoResponse getByPhone(@PathVariable("phone") String phone)throws NotFoundException{
        UserInfoResponse userInfoResponse = new UserInfoResponse();
        UserInfoEntity userInfoEntity = new UserInfoEntity();
        try{
             userInfoEntity= userService.getByPhone(phone);
        }catch (NotFoundException e)
        {
            userInfoResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return userInfoResponse;
        }
        userInfoResponse.setStatusCode(StatusEnum.SUCCESS);
        userInfoResponse.setUserInfoDto(UserMapper.INSTANCE.userInfoEntityToDto(userInfoEntity));
        return userInfoResponse;
    }
    @GetMapping("/entity/phone/{phone}")
    UserInfoEntityResponse getEntityByPhone(@PathVariable("phone") String phone)throws NotFoundException{
        UserInfoEntityResponse userInfoEntityResponse = new UserInfoEntityResponse();
        UserInfoEntity userInfoEntity = new UserInfoEntity();
        try{
            userInfoEntity= userService.getByPhone(phone);
        }catch (NotFoundException e)
        {
            userInfoEntityResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return userInfoEntityResponse;
        }
        userInfoEntityResponse.setStatusCode(StatusEnum.SUCCESS);
        userInfoEntityResponse.setUserInfoEntity(userInfoEntity);
        return userInfoEntityResponse;
    }
    @PostMapping("/register")
    RegistrationResponse register(@RequestBody UserInfoDto userInfoDto) throws BadRequestException {

        if(userService.register(userInfoDto) == -1)
        {
            return new RegistrationResponse(StatusEnum.BAD_REQUEST);
        }
        else {
            redisUtil.remove(key + "UserList");
        }
        return new RegistrationResponse(StatusEnum.SUCCESS);
    }
    @PostMapping("/update")
    UserInfoEntityResponse update(@RequestBody EditUserInfoRequest editUserInfoRequest) throws BadRequestException
    {
        try {
            redisUtil.remove(key + "UserList");
            UserInfoEntity userInfoEntity = UserMapper.INSTANCE.editUserInfoRequestToEntity(editUserInfoRequest);
            UserInfoEntity newUserInfoEntity = userService.updateInfoByPhone(userInfoEntity);
            UserInfoEntityResponse userInfoEntityResponse = new UserInfoEntityResponse();
            userInfoEntityResponse.setUserInfoEntity(newUserInfoEntity);
            userInfoEntityResponse.setStatusCode(StatusEnum.SUCCESS);
            return userInfoEntityResponse;
        }catch (NotFoundException e)
        {
            UserInfoEntityResponse userInfoEntityResponse = new UserInfoEntityResponse();
            userInfoEntityResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return userInfoEntityResponse;
        }catch (BadRequestException e)
        {
            UserInfoEntityResponse userInfoEntityResponse = new UserInfoEntityResponse();
            userInfoEntityResponse.setStatusCode(StatusEnum.BAD_REQUEST);
            return userInfoEntityResponse;
        }
    }

    @PostMapping("/phone/{phone}/uploadAvatar")
    NormalResponse uploadAvatar(@RequestParam("file") MultipartFile file, @PathVariable String phone) {
        if (file.isEmpty()) {
            return new NormalResponse(StatusEnum.BAD_REQUEST);
        }
        String suffix = file.getOriginalFilename().substring(file.getOriginalFilename().lastIndexOf("."));
        String fileName = StringUtil.allocateUuid() + suffix;//服务端文件名
        try {
            //Linux环境需修改
            File path = new File(this.getClass().getProtectionDomain().getCodeSource().getLocation().getPath());
            //File path = new File("./");
            if(!path.exists()) {
                path = new File("");
            }
            File upload = new File(path.getAbsolutePath(),fileUtil.AVATAR_PATH);
            if(!upload.exists()) {
                upload.mkdirs();
            }
            String uploadPath = upload + "\\";

            file.transferTo(new File(uploadPath+fileName));

            //更新数据库
            UserInfoEntity oldUserInfoEntity = userService.getByPhone(phone);
            oldUserInfoEntity.setIcon(uploadPath + fileName);
            userService.updateAvatarByPhone(oldUserInfoEntity);
            return new NormalResponse(StatusEnum.SUCCESS);
        }catch (NotFoundException e)
        {
            return new NormalResponse(StatusEnum.NOT_FOUND);
        }catch (Exception e)
        {
            return new NormalResponse(StatusEnum.INTERNAL_ERROR);
        }
    }

    @GetMapping("/address/{phone}")
    AddressListResponse getAllAddressByPhone(@PathVariable String phone)
    {
        AddressListResponse  addressListResponse= new AddressListResponse();
        try{
            List<AddressEntity> addressEntityList = userService.getAllAddressByPhone(phone);
            addressListResponse.setAddressList(addressEntityList);
            addressListResponse.setStatusCode(StatusEnum.SUCCESS);
        }catch (NotFoundException e)
        {
            addressListResponse.setAddressList(null);
            addressListResponse.setStatusCode(StatusEnum.NOT_FOUND);
            return addressListResponse;
        }
        return addressListResponse;
    }

    @PostMapping("/address")
    NormalResponse saveAddress(@RequestBody AddressEntity addressEntity)
    {
        NormalResponse normalResponse = new NormalResponse();
        if(userService.saveAddress(addressEntity) > 0)
        {
            normalResponse.setStatusCode(StatusEnum.SUCCESS );
        }else {
            normalResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
        }
        return normalResponse;
    }
    @GetMapping("/address/delete/{phone}/{uuid}")
    NormalResponse deleteAddressByUUid(@PathVariable String uuid, @PathVariable String phone)
    {
        NormalResponse normalResponse = new NormalResponse();
        try
        {
            userService.deleteAddressByUuid(uuid, phone);
            normalResponse.setStatusCode(StatusEnum.SUCCESS );
        }catch (Exception e)
        {
            normalResponse.setStatusCode(StatusEnum.INTERNAL_ERROR);
        }
        return normalResponse;
    }

}
