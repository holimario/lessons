omega5=349.23; %5频率
omega6=587.33; %6频率
omega2=392; %2频率
omega1=349.23; %1频率
omega61=293.66; %6.频率
f=8e3; %采样频率
%一共有三种音调持续时间,所以定义三种抽样时间
t2=[0:1/f:1];
t4=[0:1/f:0.5];
t8=[0:1/f:0.25];
%m→music,一共八个音,生成幅度为1，采样频率为8KHz的正弦信号
m1=sin(2*pi*omega5*t4);
m2=sin(2*pi*omega5*t8);
m3=sin(2*pi*omega6*t8);
m4=sin(2*pi*omega2*t2);
m5=sin(2*pi*omega1*t4);
m6=sin(2*pi*omega1*t8);
m7=sin(2*pi*omega61*t8);
m8=sin(2*pi*omega2*t2);
m=[m1,m2,m3,m4,m5,m6,m7,m8];
%sound(m);%以默认的8192采样率向扬声器发送信号
sound(m,8000);%以8K的采样率向扬声器发送信号