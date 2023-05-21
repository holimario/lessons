clear all; close all; clc;

load("hall.mat");%读取图像信息

%空域实现
test1=double(hall_gray(32:63,32:63));
imwrite(uint8(test1),"hw_2_1_1.jpg");%输出截取的一块原图
test1=test1-128*ones(32,32);
imwrite(uint8(test1),"hw_2_1_2.jpg");%输出空域操作后图像

%变换域实现
test2=double(hall_gray(32:63,32:63));
C=dct2(test2);%求解变换域矩阵
C(1,1)=C(1,1)-4096;%直流分量减去4096
test2=idct2(C);%还原到空域
imwrite(uint8(test2),"hw_2_1_3.jpg");%输出变换域操作后图像

differ=test1-test2 %比较空域实现和变换域实现的差异