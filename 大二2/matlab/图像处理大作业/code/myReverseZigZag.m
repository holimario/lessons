function info=myReverseZigZag(Z)%恢复Zig-Zag扫描的向量为矩阵
N=size(Z,1)^0.5;
info=zeros(N,N);
num=0;

for i=1:2*N-1
    if(mod(i,2)==0)
        if(i<=N)
            for j=1:i
                num=num+1;
                info(j,i-j+1)=Z(num,1);
            end
        else
            for j=1:2*N-i
                num=num+1;
                info(i+j-N,N-j+1)=Z(num,1);
            end
        end
    else
        if(i<=N)
            for j=1:i
                num=num+1;
                info(i-j+1,j)=Z(num,1);
            end
        else
            for j=1:2*N-i
                num=num+1;
                info(N-j+1,i+j-N)=Z(num,1);
            end
        end
    end
end
end
