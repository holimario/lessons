f=[523.25,523.25,587.33,392,349.23,349.23,293.66,392];
fs=8e3;
time=fs*[0.5,0.25,0.25,1,0.5,0.25,0.25,1];
%A=[1];
A=[0.54415,0.079292,0.0521705,0.0598518,0.00284736,0.00597783,0.0195305];
N=length(time);
FS=repmat(fs,N,1);
Time=time*FS/fs;%矩阵运算计算出总的抽样点个数
m=zeros(1,Time);%储存抽样点
n=1;
R=zeros(1,Time);
k=2*pi;
    for i=1:N
    t=1/fs:1/fs:time(i)/fs;
    lt=time(i);
    M=zeros(1,time(i));
    K=zeros(1,time(i));
    for q=1:length(A)
        K=K+A(q)*sin(2*pi*f(i)*q*t);
    end
    T=time(i)/fs;
    M=exp(-2.75*t/T);
    %{
    M(1:lt*0.3)=k*t(1:lt*0.3).*exp(-k*t(1:lt*0.3)/T);
    M(lt*0.3+1:lt*0.8)=M(lt*0.3);
    M(lt*0.8:end)=5*M(lt*0.8).*(-1/T*t(lt*0.8:end)+1);
    %}
    m(n:n+time(i)-1)=K.*M(1:time(i))/T;
    n=n+time(i);
    end
figure;
plot(m);
sound(m);
 
  





