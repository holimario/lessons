function [y1,y2] = analysis(w,f)
%y1返回频率，y2返回幅值；w为分析数组，f为抽样频率。
fs=f;
%fs为傅里叶变换的抽样频率
L=length(w);
y1=zeros(1,5);
y2=zeros(1,5);
%求5次谐波

Y=fft(w);
p2=abs(Y/L);%计算双侧频谱p2
p1=p2(1:L/2+1);%p2的前一半赋给p1
p1(2:end-1)=2*p1(2:end-1);%除零频之外的信号乘2
g=fs/2*linspace(0,1,L/2+1);
%plot(g,p1);

%{
%执行N点fft

NFFT=2^nextpow2(L);
y=fft(w,NFFT);
p2=abs(y/L);%计算双侧频谱p2
p1=p2(1:NFFT/2+1);%p2的前一半赋给p1
p1(2:end-1)=2*p1(2:end-1);%除零频之外的信号乘2
g=fs/2*linspace(0,1,NFFT/2+1);
%}
%fourier
Lp=length(p1);
d=ceil(L/fs);%d=1Hz的误差占几个抽样点。
for k=2:Lp-1
    if(p1(k)>0.025)&&(p1(k)>p1(k-1))&&(p1(k)>p1(k+1))
        %寻找基频
        y1(1)=g(k);
        y2(1)=p1(k);%返回基频和基频的幅值
        break
    elseif(p1(k)>0.015)&&(p1(k)>p1(k-1))&&(p1(k)>p1(k+1))
       %未找到则继续
        y1(1)=g(k);
        y2(1)=p1(k);%返回基频和基频的幅值
    end
end
for t=2:5
    for i=t*(k-d):t*(k+d)
       if(p1(k)>0.025)&&(p1(i)>p1(i-1))&&(p1(i)>p1(i+1)&&(p1(i)>p1(k)*0.05))
           y1(t)=g(i);
           y2(t)=p1(i)/y2(1);%谐波幅值归一化，方便之后设计
           break
       elseif(p1(k)>0.015)&&(p1(i)>p1(i-1))&&(p1(i)>p1(i+1)&&(p1(i)>p1(k)*0.05))
           y1(t)=g(i);
           y2(t)=p1(i)/y2(1);%谐波幅值归一化，方便之后设计
       end
    end
end
           


end

