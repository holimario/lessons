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

%单独播放每个音符
sound(note1,freq);pause(1);
sound(note2,freq);pause(1);
sound(note3,freq);pause(1);
sound(note4,freq);pause(1);
sound(note5,freq);pause(1);
sound(note6,freq);pause(1);
sound(note7,freq);pause(1);
sound(note8,freq);pause(1);

%连续播放乐曲
note=[note1 note2 note3 note4 note5 note6 note7 note8];
sound(note,freq);

function note=generatenote(tune,time)%产生相应时长与频率的正弦信号
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间
const=2^(1/12);%紧邻音调之间倍数关系
baseF=349.23;%存储F调频率

time2=0:T:2*beat;%2分音符
time4=0:T:beat;%4分音符
time8=0:T:beat/2;%8分音符

if time==2
    note=sin(2*pi*baseF*const^tune*time2);
elseif time==4
        note=sin(2*pi*baseF*const^tune*time4);
elseif time==8
        note=sin(2*pi*baseF*const^tune*time8);
end
end