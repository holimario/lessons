clear all; close all; clc;

freq=8000;%采样频率

tune_info=[7,4;7,8;9,8;2,2;0,4;0,8;-3,8;2,2];%输入乐曲信息

song=generatesong(tune_info);%生成乐曲
playsong(song,freq,tune_info);%播放乐曲

beat=0.5;
t=1;
for i=1:size(song,1)
    hold on;
    xlabel("时间/s");
    plot(t/8000:1/8000:(t+freq*beat*4/tune_info(i,2)-1)/8000,song(i,1:freq*beat*4/tune_info(i,2)));
    t=t+freq*beat*4/tune_info(i,2);
end

function envelope=generateenv(t)%产生指数衰减包络信号
envelope=exp(-4*t/max(t));
end

function note=generatenote(tune,time)%产生有包络的信号
const=2^(1/12);%紧邻音调之间倍数关系
baseF=349.23;%存储F调频率

envelope=generateenv(time);

note=sin(2*pi*baseF*const^tune*time).*envelope...
    +1.434*sin(2*2*pi*baseF*const^tune*time).*envelope...
    +0.964*sin(3*2*pi*baseF*const^tune*time).*envelope...
    +1.096*sin(4*2*pi*baseF*const^tune*time).*envelope;

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

function playsong(song,freq,tune_info)%播放乐曲
T=1/freq;%采样周期
beat=0.5;%一拍时间
sound(zeros(8000,1),freq);%稍作等待
pause(1);
for i=1:size(song,1)
    sound(song(i,1:freq*beat*4/tune_info(i,2)),freq);
    pause(beat*4/tune_info(i,2));
end
end