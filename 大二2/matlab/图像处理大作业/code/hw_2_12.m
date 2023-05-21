clear all; close all; clc;

load("hall.mat");%读取原图像信息

[DCcode,ACcode,PicHeight,PicWidth]=myJPEGencode(hall_gray,0.5);%量化步长减半的JPEG编码

save jpegcodes2 DCcode ACcode PicHeight PicWidth %存储

info=myJPEGdecode(DCcode,ACcode,PicHeight,PicWidth,0.5);%量化步长减半的JPEG解码

%计算PSNR
MSE=0;
for i=1:PicHeight
    for j=1:PicWidth
        MSE=MSE+(double(hall_gray(i,j))-double(info(i,j)))^2;
    end
end
MSE=MSE/(double(PicWidth)*double(PicHeight));
PSNR=10*log10(255^2/MSE) %输出PSNR

imwrite(info,"hw_2_12_1.jpg");%输出解码后图像