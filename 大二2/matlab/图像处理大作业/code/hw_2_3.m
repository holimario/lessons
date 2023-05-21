clear all; close all; clc;

load("hall.mat");%读取图像信息

test=double(hall_gray(40:47,40:47));%取一测试块，8×8
imwrite(uint8(test),"hw_2_3_1.jpg");%输出原测试块图像
test=test-128*ones(8,8);
C=dct2(test);
C(1:8,5:8)=0;%DCT系数的右侧四列置零
test=idct2(C);
test=test+128*ones(8,8);
imwrite(uint8(test),"hw_2_3_2.jpg");%输出右侧四列置零后图像

test=double(hall_gray(40:47,40:47));
test=test-128*ones(8,8);
C=dct2(test);
C(1:8,1:4)=0;%DCT系数的左侧四列置零
test=idct2(C);
test=test+128*ones(8,8);
imwrite(uint8(test),"hw_2_3_3.jpg");%输出左侧四列置零后图像

