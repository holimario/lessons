function PSNR=myPSNR(a,b)
PicHeight=size(a,1);
PicWidth=size(a,2);

%计算PSNR
MSE=0;
for i=1:PicHeight
    for j=1:PicWidth
        MSE=MSE+(double(a(i,j))-double(b(i,j)))^2;
    end
end
MSE=MSE/(double(PicWidth)*double(PicHeight));
PSNR=10*log10(255^2/MSE);
end