package com.xmall.xmall.utils;

import com.xmall.xmall.controller.response.NormalResponse;
import org.springframework.stereotype.Component;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * @ClassName:
 * @Description: TODO
 * @Author:Dazz1e
 * @Date:2021/12/8 下午 1:45
 * Version V1.0
 */
@Component
public class FileUtil {
    public final String AVATAR_PATH = "static/uploads/avatars/";
    public final String PRODUCT_SMALL_PATH = "static/uploads/products/small/";
    public final String PRODUCT_BIG_PATH = "static/uploads/products/big/";
    public String uploadFile(MultipartFile file, String basePath) throws Exception
    {
        if (file.isEmpty()) {
            throw new Exception();
        }
        String suffix = file.getOriginalFilename().substring(file.getOriginalFilename().lastIndexOf("."));
        String fileName = StringUtil.allocateUuid() + suffix;//服务端文件名
        try {
            //Linux环境需修改
            File path = new File(this.getClass().getProtectionDomain().getCodeSource().getLocation().getPath());
            //File path = new File("./");
            if (!path.exists()) {
                path = new File("");
            }
            File upload = new File(path.getAbsolutePath(), basePath);
            if (!upload.exists()) {
                upload.mkdirs();
            }
            String uploadPath = upload + "\\";

            file.transferTo(new File(uploadPath + fileName));
            return uploadPath + fileName;
        }catch (Exception e)
        {
            throw new Exception();
        }
    }
}


