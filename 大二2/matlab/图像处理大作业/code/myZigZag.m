function Z=myZigZag(info)
%实现Zig-Zag扫描，将矩阵变换为向量

N=size(info,1);
Z=zeros(N^2,1);
num=0;

for i=1:2*N-1
    if(mod(i,2)==0)
        %扫描方向为从右上到左下
        if(i<=N)
            %左上半区域的扫描
            for j=1:i
                num=num+1;
                Z(num,1)=info(j,i-j+1);
            end
        else
            %右下半区域的扫描
            for j=1:2*N-i
                num=num+1;
                Z(num,1)=info(i+j-N,N-j+1);
            end
        end
    else
        %扫描方向为从左下到右上
        if(i<=N)
            %左上半区域的扫描
            for j=1:i
                num=num+1;
                Z(num,1)=info(i-j+1,j);
            end
        else
            %右下半区域的扫描
            for j=1:2*N-i
                num=num+1;
                Z(num,1)=info(N-j+1,i+j-N);
            end
        end
    end
end
end