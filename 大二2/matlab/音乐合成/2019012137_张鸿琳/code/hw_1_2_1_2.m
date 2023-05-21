clear all; close all; clc;

freq=8000;%采样频率

%确定每个音符的频率和时值
note1=generatenote(7,4);
note2=generatenote(7,8);
note3=generatenote(9,8);
note4=generatenote(2,2);
note5=generatenote(0,4);
note6=generatenote(0,8);
note7=generatenote(-3,8);
note8=generatenote(2,2);

%连续播放乐曲
note=[note1 note2 note3 note4 note5 note6 note7 note8];
sound(note,freq);

function note=generatenote(tune,time)%产生有包络的信号
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间
const=2^(1/12);%紧邻音调之间倍数关系
baseF=349.23;%存储F调频率

time2=0:T:2*beat;%2分音符
time4=0:T:beat;%4分音符
time8=0:T:beat/2;%8分音符

%产生包络信号
envelope2=generateenv(time2);
envelope4=generateenv(time4);
envelope8=generateenv(time8);

if time==2
    note=sin(2*pi*baseF*const^tune*time2).*envelope2;
elseif time==4
        note=sin(2*pi*baseF*const^tune*time4).*envelope4;
elseif time==8
        note=sin(2*pi*baseF*const^tune*time8).*envelope8;
end
end

function envelope=generateenv(t)%产生指数衰减包络信号
envelope=exp(-4*t/max(t));
end

function envelope=generateenv1(t)%产生分段线性包络信号，尝试后最终没有采用该包络
envelope=10/max(t)*(t<=max(t)*0.1&t>0).*t...
+5/max(t)*(t>max(t)*0.1&t<=max(t)*0.2).*(max(t)*0.3-t)...
+0.5*(t>max(t)*0.2&t<=max(t).*0.8)...
+2.5/max(t)*(t>max(t)*0.8&t<=max(t)).*(max(t)-t);
end