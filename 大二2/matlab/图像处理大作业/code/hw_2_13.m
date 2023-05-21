clear all; close all; clc;

load("snow.mat");%读取原图像信息

imwrite(uint8(snow),"hw_2_13_1.jpg");%输出原雪花图像

[DCcode,ACcode,PicHeight,PicWidth]=myJPEGencode(snow,1);%编码

save jpegcodes3 DCcode ACcode PicHeight PicWidth %存储

info=myJPEGdecode(DCcode,ACcode,PicHeight,PicWidth,1);%解码

imwrite(info,"hw_2_13_2.jpg");%输出解码后图像

%计算PSNR
MSE=0;
for i=1:PicHeight
    for j=1:PicWidth
        MSE=MSE+(double(snow(i,j))-double(info(i,j)))^2;
    end
end
MSE=MSE/(double(PicWidth)*double(PicHeight));
PSNR=10*log10(255^2/MSE) %输出PSNR