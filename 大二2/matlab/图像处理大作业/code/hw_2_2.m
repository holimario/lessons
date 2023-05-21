clear all; close all; clc;

load("hall.mat");%读取图像信息

test=double(hall_gray(1:8,1:8));%取出一块区域数据用于测试
test=test-128*ones(8,8);%灰度值减去128
C1=myDCT(test);%利用myDCT函数进行DCT变换计算
C2=dct2(test);%利用dct2函数进行DCT变换计算
differ=C1-C2 %比较两个结果的差异


%进行DCT变换
function C=myDCT(P)
N=size(P,1);
D=zeros(N,N);

%生成D矩阵
for i=1:N
    for j=1:N
        if(i==1)
            D(i,j)=(1/2)^0.5;
        else
            D(i,j)=cos((i-1)*(2*j-1)*pi/(2*N));
        end
    end
end
D=(2/N)^0.5*D;

%得到变换域矩阵
C=D*double(P)*D.';
end