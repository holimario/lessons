clear all; close all; clc;

load("hall.mat");%读取图像信息
load("JpegCoeff.mat");%读取JPEG标准

info=hall_gray;
PicHeight=size(info,1);
PicWidth=size(info,2);
msg=zeros(1,PicHeight*PicWidth);%存储需要发送的信息

%初始化信息
for i=1:size(msg,2)
    msg(1,i)=randi([0,1]);
end

%计算DCT系数
xnum=size(info,1)/8;
ynum=size(info,2)/8;
tempinfo=double(info)-128*ones(8*xnum,8*ynum);
DCT_info=zeros(64,xnum*ynum);

%量化并存储
for i=1:xnum
    for j=1:ynum
        temp=tempinfo((i-1)*8+1:i*8,(j-1)*8+1:j*8);
        temp=dct2(temp);
        temp=round(temp./QTAB);
        temp=myZigZag(temp);
        DCT_info(:,(i-1)*ynum+j)=temp;
    end
end

%第一种DCT域信息隐藏方法
DCT_info1=DCT_info;
for i=1:size(DCT_info,1)
    for j=1:size(DCT_info,2)
        DCT_info1(i,j)=DCT_info(i,j)-...
        mod(DCT_info(i,j),2)+msg(1,(i-1)*size(DCT_info,2)+j);
    end
end
[DCcode1,ACcode1]=myJPEGencode2(DCT_info1);%编码
[info1,deDCT_info1]=myJPEGdecode2(DCcode1,ACcode1,PicHeight,PicWidth);%解码

%验证解码出的信息的正确比例
correct=0;
for i=1:size(deDCT_info1,1)
    for j=1:size(deDCT_info1,2)
        if(mod(deDCT_info1(i,j),2)==msg(1,(i-1)*size(deDCT_info1,2)+j))
            correct=correct+1;
        end
    end
end
correct_percentage1=correct/size(msg,2) %输出正确比例

compress_ratio1=PicHeight*PicWidth*8/...
(32+size(ACcode1,2)+size(DCcode1,2)) %输出压缩比

PSNR1=myPSNR(hall_gray,info1) %输出PSNR值

imwrite(info1,"hw_3_2_1.jpg");%输出第一种方法处理后图像

%第二种DCT域信息隐藏方法，把信息存在各块DCT矩阵中的靠上4行中
DCT_info2=DCT_info;
for i=1:32
    for j=1:size(DCT_info,2)
        DCT_info2(i,j)=DCT_info(i,j)-...
        mod(DCT_info(i,j),2)+msg(1,(i-1)*size(DCT_info,2)+j);
    end
end
[DCcode2,ACcode2]=myJPEGencode2(DCT_info2);%编码
[info2,deDCT_info2]=myJPEGdecode2(DCcode2,ACcode2,PicHeight,PicWidth);%解码

%验证解码出的信息的正确比例
correct=0;
for i=1:32
    for j=1:size(deDCT_info2,2)
        if(mod(deDCT_info2(i,j),2)==msg(1,(i-1)*size(deDCT_info2,2)+j))
            correct=correct+1;
        end
    end
end
correct_percentage2=correct/(32*size(deDCT_info2,2)) %输出正确比例

compress_ratio2=PicHeight*PicWidth*8/...
(32+size(ACcode2,2)+size(DCcode2,2)) %输出压缩比

PSNR2=myPSNR(hall_gray,info2) %输出PSNR值

imwrite(info2,"hw_3_2_2.jpg");%输出第二种方法处理后图像

%第三种DCT域信息隐藏方法
DCT_info3=DCT_info;
for j=1:size(DCT_info,2)
    pos=find(DCT_info(:,j)~=0);%搜索最后一个非零系数位置
    if(max(pos)==64)
        pos=63;
    else
        pos=max(pos);
    end
    if(msg(j)==0)
        DCT_info3(pos+1,j)=-1;
    else
        DCT_info3(pos+1,j)=1;
    end
end
[DCcode3,ACcode3]=myJPEGencode2(DCT_info3);%编码
[info3,deDCT_info3]=myJPEGdecode2(DCcode3,ACcode3,PicHeight,PicWidth);%解码

%验证解码出的信息的正确比例
correct=0;
for i=1:size(deDCT_info3,2)
    pos=find(deDCT_info3(:,i)~=0);%搜索最后一个非零系数位置
    pos=max(pos);
    if(deDCT_info3(pos,i)==1 && msg(1,i)==1)
        correct=correct+1;
    elseif(deDCT_info3(pos,i)==-1 && msg(1,i)==0)
        correct=correct+1;
    end
end
correct_percentage3=correct/size(deDCT_info3,2) %输出正确比例

compress_ratio3=PicHeight*PicWidth*8/...
(32+size(ACcode3,2)+size(DCcode3,2)) %输出压缩比

PSNR3=myPSNR(hall_gray,info3) %输出PSNR值

imwrite(info3,"hw_3_2_3.jpg");%输出第三种方法处理后图像
