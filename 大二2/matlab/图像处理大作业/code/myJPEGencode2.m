function [DCcode,ACcode]=myJPEGencode2(DCT_info)
load("JpegCoeff.mat");

DCcode=[];
ACcode=[];

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
        temp=floor(log2(abs(DCtemp2(1,i))))+1;
        temp0=dec2bin(abs(DCtemp2(1,i)),temp)-'0';
        if(DCtemp2(1,i)<0)%取补码
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
    zeronum=0;
    zrlnum=0;
    for j=2:64
        if(DCT_info(j,i)==0)
            zeronum=zeronum+1;
            if(zeronum==16)%记录ZRL个数
                zrlnum=zrlnum+1;
                zeronum=0;
            end
        else
            tempx=[1,1,1,1,1,1,1,1,0,0,1];
            temp=repmat(tempx,1,zrlnum);
            ACcode=[ACcode,temp];%插入ZRL
            zrlnum=0;

            temp=floor(log2(abs(DCT_info(j,i))))+1;
            temp0=dec2bin(abs(DCT_info(j,i)),temp)-'0';
            if(DCT_info(j,i)<0)
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

end
