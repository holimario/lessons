clear all; close all; clc;

load("hall.mat");%读取图像信息

info=hall_gray;
msg=zeros(1,size(hall_gray,1)*size(hall_gray,2));%存储要发送的信息

%初始化信息
for i=1:size(msg,2)
    msg(1,i)=randi([0,1]);
end

%将信息存入像素灰度值比特最低位
for i=1:size(info,1)
    for j=1:size(info,2)
        info(i,j)=info(i,j)-mod(info(i,j),2)+msg(1,(i-1)*size(info,2)+j);
    end
end

imwrite(hall_gray,"hw_3_1_1.jpg");%输出插入信息前的原图像
imwrite(info,"hw_3_1_2.jpg");%输出插入信息后的图像
[DCcode,ACcode,PicHeight,PicWidth]=myJPEGencode(info,1);%编码

decode_info=myJPEGdecode(DCcode,ACcode,PicHeight,PicWidth,1);%解码

%验证解码出的信息的正确比例
correct=0;
for i=1:size(info,1)
    for j=1:size(info,2)
        if(bitget(decode_info(i,j),1)==msg(1,(i-1)*size(info,2)+j))
            correct=correct+1;
        end
    end
end
correct_percentage=correct/size(msg,2) %输出正确比例
