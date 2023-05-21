clear all; close all; clc;

test=1:64;
test=reshape(test,8,8);%生成一从1到64的8×8矩阵
test=test.';
Z=myZigZag(test).' %输出扫描结果