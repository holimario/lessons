function info=myJPEGdecode(DCcode,ACcode,PicHeight,PicWidth,step)
load("JpegCoeff.mat");

QTAB=step*QTAB;%调整步长

xnum=PicHeight/8;
ynum=PicWidth/8;
DCT_info=zeros(64,xnum*ynum);

%对DC码流进行解码
num=0;
i=1;
k=1;
cate=[];
while i<size(DCcode,2)
    num=num+1;
    if(num>=2)
        cate=find(DCTAB==num);
    end
    if(~isempty(cate))
        for j=cate.'
            if(all(DCTAB(j,2:1+num)==DCcode(1,i-num+1:i)))
                if(num==2)
                    DCT_info(1,k)=0;
                else
                    DCT_info(1,k)=myBin2Dec(DCcode(1,i+1:i+j-1));
                    i=i+j-1;
                end
                k=k+1;
                num=0;
                break;
            end
        end
        cate=[];
    end
    i=i+1;
end

%DC系数差分的逆运算
for i=2:size(DCT_info,2)
    DCT_info(1,i)=DCT_info(1,i-1)-DCT_info(1,i);
end

%对AC码流进行解码
k=1;%记录ACcode的位置
t=2;%记录是第几个AC系数
codelen=0;
siz=0;%AC编码中的size
zeronum=0;%存储前面零个数
ZRL=[1,1,1,1,1,1,1,1,0,0,1];
EOB=[1,0,1,0];
for i=1:size(DCT_info,2)
    while 1
        codelen=codelen+1;
        if(codelen==11 && all(ACcode(1,k-codelen+1:k)==ZRL))
            codelen=0;
            zeronum=zeronum+16;
        else
            pos=find(ACTAB(:,3)==codelen);
            if(~isempty(pos))
                for j=pos.'
                    if(all(ACTAB(j,4:3+codelen)==ACcode(1,k-codelen+1:k)))
                        zeronum=zeronum+ACTAB(j,1);%跳过零
                        siz=ACTAB(j,2);
                        t=t+zeronum;
                        DCT_info(t,i)=myBin2Dec(ACcode(1,k+1:k+siz));
                        t=t+1;
                        k=k+siz;
                        zeronum=0;
                        codelen=0;
                        break;
                    end
                end
                pos=[];
            end
        end
        if(codelen==4 && all(ACcode(1,k-codelen+1:k)==EOB))%读取到结尾
            k=k+1;
            codelen=0;
            t=2;
            zeronum=0;
            break;
        end
        k=k+1;
    end
end

%进一步解码出图片信息
for i=1:xnum
    for j=1:ynum
        temp=DCT_info(:,(i-1)*ynum+j);
        temp=myReverseZigZag(temp);
        temp=temp.*QTAB;
        temp=idct2(temp);
        info((i-1)*8+1:i*8,(j-1)*8+1:j*8)=temp;
    end
end
info=info+128*ones(8*xnum,8*ynum);
info=uint8(info);
end
