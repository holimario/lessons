clear all; close all; clc;

image=imread("test.jpg");%读取检测人脸的图像信息
image=imadjust(image,[.2 .3 0; .6 .7 1],[]);%改变颜色
test=image;%暂存图像信息

L=5;%确定RGB值的比特位数

v=myTraining(L);%利用样本进行训练得到v

%修改以下参数来改善检测结果
ratioh=5;%人脸在图片高度所占最大比例的倒数
ratiow=5;%人脸在图片宽度所占最大比例的倒数
e=0.63;%距离阈值
num=20;%人脸占图比例最小值
step=10;%每次移动的像素数
ratio=1.8;%人脸图框比例极限
deepnum=6;%再进一步深入检测次数
loose=0.05;%深入检测时放宽的距离阈值

h1=floor(size(test,1)/ratioh);%高度迈进步长初始值
w1=floor(size(test,2)/ratiow);%宽度迈进步长初始值
h2=floor(size(test,1)/num);%高度迈进步长终止值
w2=floor(size(test,2)/num);%宽度迈进步长终止值

facepos=[];%记录人脸位置和大小信息
flag=0;%标志是否检测到了人脸

deep=0;%深入检测次数
facenum=0;%检测到的人脸数

while 1
    flag=0;
    for h=h1:-step:h2
        for w=w1:-step:w2
            if(w/h<1/ratio)
                break;
            end
            if(w/h>ratio)
                continue;
            end
            i=1;
            while i+h-1<=size(test,1)
                j=1;
                while j+w-1<=size(test,2)
                    u=myCalculate(test(i:i+h-1,j:j+w-1,:),L);
                    if(myDistance(u,v)<e)
                        flag=1;
                        facepos=[facepos;i,j,h,w];%存储已检测到的人脸信息
                        test(i:i+h-1,j:j+w-1,1:3)=0;%清除已检测到的人脸
                        break;
                    end
                    j=j+w;
                end
                i=i+h;
                if(flag==1)
                    break;
                end
            end
            if(flag==1)
                break;
            end
        end
        if(flag==1)
            facenum=facenum+1 %输出当前检测到的人脸数量
            break;
        end
    end
%若需要加快检测速度，可以加上下面的代码，限制图框大小变化范围
%     if(facenum==1)
%         h1=h+4*step;
%         w1=w+4*step;
%     end
    if(flag==0)
        if(deep==deepnum)%放宽距离阈值，进一步检测
            break;
        else
            e=e+loose;
            deep=deep+1;
        end
    end
end

image=myDrawFrame(facepos,image);%画上红色图框
imwrite(image,"hw_4_3_3.jpg");%输出检测结果
