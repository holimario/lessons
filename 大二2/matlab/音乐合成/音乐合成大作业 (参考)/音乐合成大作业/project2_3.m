load('Guitar.MAT');
rewave=repmat(wave2proc,500,1);%将时域信号重复500次
L=length(rewave);%定义时域抽样点数
fs=8e3;
T=L/fs;%区间长度

y=fft(rewave);
p2=abs(y/L);%计算双侧频谱p2
p1=p2(1:L/2+1);%p2的前一半赋给p1
p1(2:end-1)=2*p1(2:end-1);%除零频之外的信号乘2
g=fs/2*linspace(0,1,L/2+1);
plot(g,p1);

%{
NFFT=2^nextpow2(L);
%执行N点fft
NFFT=2^nextpow2(L);
y=fft(rewave,NFFT);
p2=abs(y/L);%计算双侧频谱p2
p1=p2(1:NFFT/2+1);%p2的前一半赋给p1
p1(2:end-1)=2*p1(2:end-1);%除零频之外的信号乘2
g=fs/2*linspace(0,1,NFFT/2+1);
plot(g,p1);
%}

%%{
%选出幅值最大的5个频率及其幅度
mn=1;
while mn<=5
    [r,index]=max(p1);
    p1(index)=[];
    if g(index)>200
        anm(2,mn)=g(index);
        anm(1,mn)=r;
        mn=mn+1;
    end
end
%}