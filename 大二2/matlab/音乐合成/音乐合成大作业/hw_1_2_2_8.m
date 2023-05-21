clear all; close all; clc;

load("Guitar.MAT");%读取文件

%通过取平均消除非线性谐波和噪声
%为了让结果更精准，先通过重新取样增加点的密度
res_wave=resample(realwave,100,1);
temp=zeros(1,size(res_wave,1));%暂存自相关数据

%计算(自相关函数)/(偏移后自身重叠区间长度)，便于确定峰值
for i=1:size(res_wave,1)
    temp(1,i)=sum(res_wave(i:size(res_wave,1)).*...
        res_wave(1:size(res_wave,1)-i+1))/(size(res_wave,1)-i+1);
end

peak=zeros(1,10);
k=1;

%找到(自相关函数)/(偏移后自身重叠区间长度)的极值点，确定周期
for i=2:size(temp,2)-1 
	%不是所有极值点都是周期交界点，其需要大于某一值
    if(temp(1,i)>0.006 && temp(1,i)>=temp(1,i-1) && temp(1,i)>=temp(1,i+1))
        peak(1,k)=i;
        k=k+1;
    end
end

%根据所得周期交界点，将原信号拆分为多个单周期信号求平均
len=2430;
aver=res_wave(1:len);
for i=1:8
    aver=aver+res_wave(peak(1,i):peak(1,i)+len-1);
end
aver=aver/9;

processed_wave=[aver;aver;aver;aver;aver;aver;aver;aver;aver;aver];
processed_wave=[processed_wave;processed_wave;processed_wave;...
                processed_wave;processed_wave;processed_wave;...
                processed_wave;processed_wave;processed_wave;...
                processed_wave];%重复10次便于进行傅里叶变换分析
processed_wave=resample(processed_wave,1,100);

%利用老师所给prefourier函数做傅里叶变换
Trg=[0,243/8000*10];
N=2430;
OMGrg=[-8000*pi,8000*pi];
K=20000;
[omg,FT]=prefourier(Trg,N,OMGrg,K);
F_info=FT*processed_wave;

%绘制频域图像
plot(omg/2/pi,abs(F_info));
xlabel("频率/Hz");
ylabel("|F(j\omega)|");

function [omg,FT]=prefourier(Trg,N,OMGrg,K)
% 输入参数： 
% Trg  : 二维矢量，两个元素分别表示时域信号的起止时间；
% N    : 时域抽样数量；
% OMGrg: 二维矢量，两个元素分别表示频谱的起止频率；
% K    : 频域抽样数量。
% 输出参数：
% omg  : 抽样频率；
% FT   : 实现傅里叶变换的矩阵~U~及系数；
T=Trg(2)-Trg(1);
t=linspace(Trg(1),Trg(2)-T/N,N)';
OMG=OMGrg(2)-OMGrg(1);
omg=linspace(OMGrg(1),OMGrg(2)-OMG/K,K)';
FT=T/N*exp(-1i*kron(omg,t.'));
end