clear all; close all; clc;

load("hall.mat");%读取图片信息

test=double(hall_gray(40:47,40:47));
test=test-128*ones(8,8);
C=dct2(test);
C=C.';
test=idct2(C);
test=test+128*ones(8,8);
imwrite(uint8(test),"hw_2_4_1.jpg");%输出DCT系数转置后的图像

test=double(hall_gray(40:47,40:47));
test=test-128*ones(8,8);
C=dct2(test);
C=rot90(C);
test=idct2(C);
test=test+128*ones(8,8);
imwrite(uint8(test),"hw_2_4_2.jpg");%输出DCT系数旋转90度后的图像

test=double(hall_gray(40:47,40:47));
test=test-128*ones(8,8);
C=dct2(test);
C=rot90(rot90(C));
test=idct2(C);
test=test+128*ones(8,8);
imwrite(uint8(test),"hw_2_4_3.jpg");%输出DCT系数旋转180度后的图像