clc;close all;clear;
s_rate = 51.15;%采样频率
rate = 10.23;%PRN序列频率
ratio = round(s_rate/rate);%采样频率和PRN序列频率之比

%读取文件
fid = fopen('C:\Users\惠普\Desktop\DSP大作业\DSP大作业\UEQ_rawFile_16bit_Task1.dat', 'r');
dataLen = inf;
[data, count] = fread(fid, dataLen ,'int16');
load("B3I_Codes.mat");
M = 10230*ratio;

% temp = repelem(B3I_Codes(1,:),ratio);
% [temp,x] = xcorr(data',temp);
% figure(1);
% plot(x(4900000:5500000),temp(4900000:5500000))

data = [zeros(1,M-1),data(:,1)'];%存储信号序列并补零方便进行互相关运算
init = zeros(1,63);%存储PRN序列自相关函数R(0)大小
relation = zeros(1,size(data,2)+2*M);%保存互相关函数序列

L = 2^19;%给出FFT序列长度
prn = B3I_Codes(1,:);
prn = fliplr(repelem(prn,ratio));
prn = [prn,zeros(1,L-M)];%补零
x = fft(prn);

%重叠保留法
k = 0;
while (k+1)*(L-M+1)+M-1 <= size(data,2)
    y = fft(data(1,(k*(L-M+1)+1):((k+1)*(L-M+1)+M-1)));
    z = ifft(x.*y);
    relation(1,(k*(L-M+1)+1):((k+1)*(L-M+1))) = z(1,M:L);
    k = k+1;
end

% [relation,x] = xcorr(data(M:length(data)),repelem(B3I_Codes(1,:),ratio));

plot(relation);
