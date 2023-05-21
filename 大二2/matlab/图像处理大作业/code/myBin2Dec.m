function dec=myBin2Dec(bin)%把二进制数组转化为十进制数值
dec=0;

if(bin(1,1)==0)
    temp=~bin;
    sign=-1;
else
    temp=bin;
    sign=1;
end

N=size(bin,2)-1;
for i=0:N
    dec=dec+temp(1,i+1)*2^(N-i);
end
dec=dec*sign;
end