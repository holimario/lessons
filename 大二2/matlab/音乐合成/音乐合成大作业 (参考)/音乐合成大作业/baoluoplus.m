function m = baoluoplus(fs,f,time)%f为各乐音对应频率，time为乐音持续时间对应的抽样点数,fs为抽样频率
N=length(time);
FS=repmat(fs,N,1);
Time=time*FS/fs;%通过矩阵运算计算出总抽样点个数
m=zeros(1,Time);%储存抽样点
n=1;
R=zeros(1,Time);
k=2*pi;
    for i=1:N
    t=1/fs:1/fs:time(i)/fs;
    lt=time(i);
    M=zeros(1,time(i));
    T=time(i)/fs;
    M(1:lt*0.3)=k*t(1:lt*0.3).*exp(-k*t(1:lt*0.3)/T);
    M(lt*0.3+1:lt*0.8)=M(lt*0.3);
    M(lt*0.8:end)=5*M(lt*0.8).*(-1/T*t(lt*0.8:end)+1);
    m(n:n+time(i)-1)=sin(2*pi*f(i)*t).*M(1:time(i))/T;
    n=n+time(i);
    end
end

