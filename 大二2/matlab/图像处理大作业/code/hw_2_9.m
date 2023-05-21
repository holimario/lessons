clear all; close all; clc;

load("hall.mat");%读取图像信息
load("JpegCoeff.mat");%读取JPEG标准

DCcode=[];%存储DC码流
ACcode=[];%存储AC码流

%补全为8的倍数
image=zeros(8*ceil(size(hall_gray,1)/8),8*ceil(size(hall_gray,2)/8));
image(1:size(hall_gray,1),1:size(hall_gray,2))=hall_gray;
image=uint8(image);

PicHeight=uint16(size(image,1));%存储图片高度
PicWidth=uint16(size(image,2));%存储图片宽度

%先计算DCT系数并量化
xnum=size(image,1)/8;
ynum=size(image,2)/8;
info=double(image)-128*ones(8*xnum,8*ynum);
DCT_info=zeros(64,xnum*ynum);

for i=1:xnum
    for j=1:ynum
        temp=info((i-1)*8+1:i*8,(j-1)*8+1:j*8);
        temp=dct2(temp);
        temp=round(temp./QTAB);
        temp=myZigZag(temp);
        DCT_info(:,(i-1)*ynum+j)=temp;
    end
end

%对DC系数进行差分
DCtemp1=DCT_info(1,:);
DCtemp2=DCtemp1;
for i=2:size(DCtemp1,2)
    DCtemp2(1,i)=DCtemp1(1,i-1)-DCtemp1(1,i);
end

%对DC系数进行编码
for i=1:size(DCtemp2,2)
    if(DCtemp2(1,i)==0)
        temp=[0,0];
    else
        temp=floor(log2(abs(DCtemp2(1,i))))+1;%计算相应Category
        temp0=dec2bin(abs(DCtemp2(1,i)),temp)-'0';%计算二进制表示
        if(DCtemp2(1,i)<0)%若为负数则取1的补码
            temp0=~temp0;
        end
        temp=DCTAB(temp+1,2:DCTAB(temp+1,1)+1);
        temp=[temp,temp0];
    end
    DCcode=[DCcode,temp];
end
DCcode=logical(DCcode);

%对AC系数进行编码
for i=1:size(DCT_info,2)
    zeronum=0;%记录零系数个数
    zrlnum=0;%记录ZRL个数
    for j=2:64
        if(DCT_info(j,i)==0)
            zeronum=zeronum+1;
            if(zeronum==16)
                zrlnum=zrlnum+1;
                zeronum=0;
            end
        else
            tempx=[1,1,1,1,1,1,1,1,0,0,1];%ZRL码
            temp=repmat(tempx,1,zrlnum);
            ACcode=[ACcode,temp];%插入ZRL
            zrlnum=0;

            temp=floor(log2(abs(DCT_info(j,i))))+1;%计算Size
            temp0=dec2bin(abs(DCT_info(j,i)),temp)-'0';%计算二进制表示
            if(DCT_info(j,i)<0)%若为负数则取1的补码
                temp0=~temp0;
            end
            temp=ACTAB(zeronum*10+temp,4:ACTAB(zeronum*10+temp,3)+3);
            temp=[temp,temp0];
            zeronum=0;
            ACcode=[ACcode,temp];
        end
    end
    temp=[1,0,1,0];
    ACcode=[ACcode,temp];%插入EOB
end
ACcode=logical(ACcode);

save jpegcodes DCcode ACcode PicHeight PicWidth %存储
