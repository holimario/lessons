clear all; close all; clc;

load("hall.mat");%读取图像信息
load("JpegCoeff.mat");%读取JPEG标准

xnum=size(hall_gray,1)/8;
ynum=size(hall_gray,2)/8;
info=double(hall_gray)-128*ones(8*xnum,8*ynum);%灰度值减去128
DCT_info=zeros(64,xnum*ynum);

%按照8×8的块依次进行DCT、量化，将其Zig-Zag扫描后存入DCT_info
for i=1:xnum
    for j=1:ynum
        temp=info((i-1)*8+1:i*8,(j-1)*8+1:j*8);
        temp=dct2(temp);
        temp=round(temp./QTAB);
        temp=myZigZag(temp);
        DCT_info(:,(i-1)*ynum+j)=temp;
    end
end