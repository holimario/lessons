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
m1=xiebo(omega5,t4);
m2=xiebo(omega5,t8);
m3=xiebo(omega6,t8);
m4=xiebo(omega2,t2);
m5=xiebo(omega1,t4);
m6=xiebo(omega1,t8);
m7=xiebo(omega61,t8);
m8=xiebo(omega2,t2);
R1=baoluo(m1,t4);
R2=baoluo(m2,t8);
R3=baoluo(m3,t8);
R4=baoluo(m4,t2);
R5=baoluo(m5,t4);
R6=baoluo(m6,t8);
R7=baoluo(m7,t8);
R8=baoluo(m8,t2);

R=[R1 R2 R3 R4 R5 R6 R7 R8]*2.5;


figure;
hold on;
plot(R);

sound(R);%以默认的8192采样率向扬声器发送信号

