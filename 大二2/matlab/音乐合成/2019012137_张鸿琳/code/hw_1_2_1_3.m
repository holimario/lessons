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
sound(note,freq*2);%高八度
pause(3);
sound(note,freq/2);%低八度
pause(8);

note_new=resample(note,1000,1059);%升高半个音阶
sound(note_new,freq);

function note=generatenote(tune,time)%产生有包络的信号
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间
const=2^(1/12);%紧邻音调之间倍数关系
baseF=349.23;%存储F调频率

time2=0:T:2*beat;%2分音符
time4=0:T:beat;%4分音符
time8=0:T:beat/2;%8分音符

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