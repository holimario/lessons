clear all; close all; clc;

%演奏欢乐颂前四个小节

freq=8000;%采样频率
singletime=0.5;%切换播放音符的时间

tune_info=[16,4;16,4;17,4;19,4;19,4;17,4;16,4;14,4;12,4;...
    12,4;14,4;16,4;16,8/3;14,4;14,2];%输入乐曲信息

song=generatesong(tune_info);%生成乐曲
playsong(song,freq,singletime,tune_info);%播放乐曲

function envelope=generateenv(t)%产生指数衰减包络信号
envelope=exp(-4*t/max(t));
end

function note=generatenote(tune,time)%产生有包络的信号
const=2^(1/12);%紧邻音调之间倍数关系
baseD=293.66;%存储D调频率

envelope=generateenv(time);

note=sin(2*pi*baseD*const^tune*time).*envelope...
    +0.2*sin(2*2*pi*baseD*const^tune*time).*envelope...
    +0.3*sin(3*2*pi*baseD*const^tune*time).*envelope;

end

function song=generatesong(tune_info)%生成乐曲
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间

song=zeros(size(tune_info,1),freq*beat*2);

for i=1:size(tune_info,1)
    t=0:T:beat*4/tune_info(i,2);
    temp=generatenote(tune_info(i,1),t);
    song(i,1:size(temp,2))=temp;
end
end

function playsong(song,freq,singletime,tune_info)%播放乐曲
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间
sound(zeros(8000,1),freq);%稍作等待
pause(1);
for i=1:size(song,1)
    sound(song(i,1:freq*beat*4/tune_info(i,2)),freq);
    pause(singletime);
end
end