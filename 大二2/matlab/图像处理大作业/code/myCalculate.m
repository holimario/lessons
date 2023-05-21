function u=myCalculate(image,L)
colornum=2^(3*L);%颜色的数量
u=zeros(colornum,1);

for m=1:size(image,1)
    for n=1:size(image,2)
        k=bitshift(floor(double(image(m,n,1))/(2^(8-L))),2*L)+...
        bitshift(floor(double(image(m,n,2))/(2^(8-L))),L)+...
        floor(double(image(m,n,3))/(2^(8-L)));
        u(k+1,1)=u(k+1,1)+1;
    end
end
u=u/(size(image,1)*size(image,2));

end