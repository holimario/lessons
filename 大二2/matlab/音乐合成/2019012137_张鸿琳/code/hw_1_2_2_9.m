clear all; close all; clc;

[y,Fs]=audioread("fmt.wav");%读取文件

freq=8000;%采样频率

%通过峰值统计音符时值
time=zeros(50,1);%存储音符时值
pos=zeros(50,1);%存储音符起始点与终止点
pos(1)=352;%设定音符起始点
jump=0.25*8000;%各个音符时域的最小单位为0.25s
range=500;%临近音符允许的相交部分
range0=500;%确定和前面比较的范围，用于找跳变值
range1=300;%确定和前面比较的范围，用于找跳变值
ratio=1.5;%跳变程度
num=2;%存储音符数量
for i=201:size(y,1)
    if(i-pos(num-1,1)>jump-range)
        [temp,temp1]=max(y(i-range0:i-range1,1));
        if(y(i,1)>0 && y(i,1)/temp>ratio)
            pos(num,1)=i;
            time(num-1,1)=round((i-pos(num-1,1))/jump);
            num=num+1;
        end
    end
end
num=num-1;
time(num,1)=round((size(y,1)-pos(num-1,1))/jump);

%绘制各个音符对应的时域范围
figure(1);
hold on
plot(y);
a=pos(1:num,1);
b=ones(num,1);
stem(a,b,'Marker','none');

%通过prefourier函数确定各个音符的音调
tunes=zeros(num,1);%存储音符音调信息
pos(num+1,1)=size(y,1);
harmonic_info=zeros(num,3);%存储各个谐波分量归一化峰值信息
x=200;%用于取音符时域的中间部分
for i=1:num
    Trg=[0,(pos(i+1,1)-pos(i,1)+1-x)/8000];
    N=pos(i+1,1)-pos(i,1)+1-x;
    OMGrg=[-4000*pi,4000*pi];
    K=20000;
    [omg,FT]=prefourier(Trg,N,OMGrg,K);
    F_info=FT*y(pos(i,1):pos(i+1,1)-x,1);
    [tunes(i,1),harmonic_info(i,:)]=gettune(omg/2/pi,abs(F_info(10001:20000,1)));
end

% tunes(26,1)=247;%可能需要对该音调进行修正

tune_info=analyze(time,tunes,num);%对得到的初步信息进行整合
% song=generatesong(tune_info,harmonic_info);%利用提取出的音调和时值信息生成曲子
% playsong(song,freq,tune_info);%播放曲子

function [omg,FT] = prefourier(Trg,N,OMGrg,K)
% 输入参数： 
% Trg  : 二维矢量，两个元素分别表示时域信号的起止时间；
% N    : 时域抽样数量；
% OMGrg: 二维矢量，两个元素分别表示频谱的起止频率；
% K    : 频域抽样数量。
% 输出参数：
% omg  : 抽样频率；
% FT   : 实现傅里叶变换的矩阵~U~及系数；
T = Trg(2)-Trg(1);
t = linspace(Trg(1),Trg(2)-T/N,N)';
OMG = OMGrg(2)-OMGrg(1);
omg = linspace(OMGrg(1),OMGrg(2)-OMG/K,K)';
FT = T/N*exp(-1i*kron(omg,t.'));
end

function [tune,harmonic]=gettune(omg,F)%由傅里叶变换图像找基波和谐波信息
harmonic=zeros(1,3);%存储谐波信息
ratiox=0.71;
temp=zeros(4,1);
pos=zeros(4,1);
t=60;
[temp(1,1),pos(1,1)]=max(F);
if(omg(10000+pos(1,1),1)>500)
    [temp(1,1),pos(1,1)]=max(F(1:pos(1,1)-t,1));
end
if(omg(10000+pos(1,1),1)>500)
    [temp(1,1),pos(1,1)]=max(F(1:pos(1,1)-t,1));
end
[temp(2,1),pos(2,1)]=max(F(1:pos(1,1)-t,1));
[temp(3,1),pos(3,1)]=max(F(1:pos(2,1)-t,1));
[temp(4,1),pos(4,1)]=max(F(1:pos(3,1)-t,1));
res=pos(1,1);
tt=60;
ratioy=0.5;
for i=2:4
    if(temp(i)>ratiox*temp(1,1))
        x=max(F(2*res-tt:2*res+tt,1));
        if(x<ratioy*F(res,1))%若二次谐波分量很小
            res=pos(i,1);
        end
    end
end

tune=abs(omg(10000+res,1));
tt=50;
harmonic(1,1)=max(F(res-tt:res+tt,1));
for i=2:3
    if(i*res<=size(F,1))
        harmonic(1,i)=max(F(i*res-tt:i*res+tt,1))/harmonic(1,1);
    end
end
harmonic(1,1)=1;
end

function envelope=generateenv(t)%产生指数衰减包络信号
envelope=exp(-4*t/max(t))/max(t);
end

function note=generatenote(tune,time,harmonic)%产生有包络的信号
const=2^(1/12);%紧邻音调之间倍数关系
baseA=220;%存储A调频率

envelope=generateenv(time);

note=harmonic(1,1)*sin(2*pi*baseA*const^tune*time).*envelope...
    +harmonic(1,2)*sin(2*2*pi*baseA*const^tune*time).*envelope...
    +harmonic(1,3)*sin(3*2*pi*baseA*const^tune*time).*envelope;

end

function tune_info=analyze(time,tunes,num)%用于将提取出的初步信息进行整理
baseA=220;

tune_info=zeros(num,2);
for i=1:num
    tune_info(i,1)=round(12*log2(tunes(i,1)/baseA));
    tune_info(i,2)=8/time(i,1);
end
end

function song=generatesong(tune_info,harmonic_info)%由提取出的音调和时值信息生成曲子
freq=8000;%采样频率
T=1/freq;%采样周期
beat=0.5;%一拍时间

song=zeros(size(tune_info,1),freq*beat*2);

for i=1:size(tune_info,1)
    t=0:T:beat*4/tune_info(i,2);
    temp=generatenote(tune_info(i,1),t,harmonic_info(i,:));
    song(i,1:size(temp,2))=temp;
end
end

function playsong(song,freq,tune_info)%播放曲子
T=1/freq;%采样周期
beat=0.5;%一拍时间
sound(zeros(8000,1),freq);%稍作等待
pause(1);
for i=1:size(song,1)
    sound(song(i,1:freq*beat*4/tune_info(i,2)),freq);
    pause(beat*4/tune_info(i,2));
end
end