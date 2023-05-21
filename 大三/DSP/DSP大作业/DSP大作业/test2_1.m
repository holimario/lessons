clc;close all;clear;
s_rate = 51.15;%采样频率
rate = 10.23;%PRN序列频率
ratio = round(s_rate/rate);%采样频率和PRN序列频率之比

%读取文件
fid = fopen('UEQ_rawFile_16bit_Task2.dat', 'r');
dataLen = inf;
[data, count] = fread(fid, dataLen ,'int16');
load("B3I_Codes.mat");
M = 10230*ratio;
cyc = M;%一个匹配周期

t1 = clock;
data = [zeros(1,M-1),data(:,1)'];%存储信号序列并补零方便进行互相关运算
sp = shiftplus(data(M:length(data)),cyc,150);
sp = [zeros(1,M-1),sp];

sate = [];%记录检测到的卫星序号
A = zeros(1,63);%存储检测到的卫星信号的强度
D = zeros(1,63);%存储检测到的卫星信号的延时

L = 2^16;%给出FFT序列长度
w = 1.12;%判定弱信号存在的限度
b = 4;
c = 50000;
cycnum = 7;
init = 0;%是否初始化了
spfft = zeros(100,L);%存储sp信号的fft结果

%遍历63个PRN序列进行检测
for p = 11:20
    p
    prn = zeros(1,cyc+L-M);%补零
    prn(1:cyc) = fliplr(repelem(B3I_Codes(p,:),ratio));%提高PRN序列采样率，使其和输入信号采样率一致
    x = fft(prn);%计算PRN序列的DFT
    relation = zeros(1,size(data,2)+2*M);%存储互相关函数序列

    flag = 0;
    detect = 0;

    %重叠保留法，先判定卫星信号强弱
    k = 0;
    while (k+1)*(L-M+1)+M-1 <= cyc*cycnum
        if (init == 0)
            y = fft(sp(1,(k*(L-M+1)+1):((k+1)*(L-M+1)+M-1)));
            spfft(k+1,:) = y;
        else
            y = spfft(k+1,:);
        end
        z = ifft(x.*y);
        relation(1,(k*(L-M+1)+1):((k+1)*(L-M+1))) = z(1,M:L);
        k = k+1;

        if (flag == 0 && (k+1)*(L-M+1) >= 2*cyc)
            flag = 1;
            [maxone,maxpos] = max(abs(relation(cyc+1:2*cyc)));
            compa = max(abs(relation(cyc+maxpos-c:cyc+maxpos-b)));
            compb = max(abs(relation(cyc+maxpos+b:cyc+maxpos+c)));
            if (maxone >= w*compa && maxone >= w*compb)
                detect = 1;%发现卫星信号
            end
        end
    end
    init = 1;%初始化完毕，不用重复计算fft

    if (detect == 1)
        maxone = relation(cyc+maxpos);
        [~,pos1] = max(abs(relation(2*cyc+maxpos-2:2*cyc+maxpos+2)));
        temp1 = relation(2*cyc+maxpos-3+pos1);
        [~,pos2] = max(abs(relation(3*cyc+maxpos-2:3*cyc+maxpos+2)));
        temp2 = relation(3*cyc+maxpos-3+pos2);
        [~,pos3] = max(abs(relation(4*cyc+maxpos-2:4*cyc+maxpos+2)));
        temp3 = relation(4*cyc+maxpos-3+pos3);
        A(p) = (maxone+temp1+temp2+temp3)/(4*cyc);
        D(p) = maxpos;
        sate = [sate,p];
    end
    figure(p);
    plot(relation(1:((k+1)*(L-M+1))));
end

t2 = clock;
etime(t2,t1)

% figure(1);
% plot(A);
% figure(2);
% plot(D);

function y = shiftplus(seq,s,n)%用于检测弱卫星信号
temp = size(seq,2);
temp2 = floor(temp/n);
y = zeros(1,temp2);
m = floor(temp2/s);

for l = 1:m
    temp_seq = zeros(1,s);
    for k = 1:n
        if (s*(l-1)*n+s*k<=temp)
            temp_seq = temp_seq+seq(1,(s*(l-1)*n+s*(k-1)+1):(s*(l-1)*n+s*k));
        else
            k = k-1;
            break
        end
    end
    y(1,s*(l-1)+1:s*l) = temp_seq/k;
end
end

