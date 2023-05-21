clear all; close all; clc;

load("Guitar.MAT");%读取文件

figure(1);
plot(realwave);%绘制realwave图像
title("realwave");
figure(2);
plot(wave2proc);%绘制wave2proc图像
title("wave2proc");

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

%对所得平均信号进行周期延拓
processed_wave=[aver;aver;aver;aver;aver;aver;aver;aver;aver;aver];
processed_wave=resample(processed_wave,1,100);

%将利用上述操作得到的波形与wave2proc进行对比
figure(3);
plot(processed_wave);
title("processed\_wave");
figure(4);
hold on;
plot(processed_wave);
plot(wave2proc);
title("processed\_wave+wave2proc");
