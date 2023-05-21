clear all; close all; clc;

load("hall.mat");%读取文件
imwrite(hall_color,"hw_1_2_1.jpg");%输出原图片

%给测试图像中心加上一红色实心圆
test1=hall_color;
a=size(hall_color,1);
b=size(hall_color,2);
R=min(a,b);
for i=1:a
    for j=1:b
        %若像素点位置位于圆区域内，则改变其RGB值为纯红色
        if((i-a/2)^2+(j-b/2)^2<=R^2/4)
            test1(i,j,1)=255;
            test1(i,j,2)=0;
            test1(i,j,3)=0;
        end
    end
end
imwrite(test1,"hw_1_2_2.jpg");%输出画上圆的图像

%将测试图像涂成"黑白格"的样子
test2=hall_color;
num=8;%行和列的分格数
x=a/num;
y=b/num;
for i=1:a
    for j=1:b
        %格数（行或列）每变动一个，则黑白发生一次变化
        if(mod(floor((i-1)/x)+floor((j-1)/y),2)==0)
            test2(i,j,1)=0;
            test2(i,j,2)=0;
            test2(i,j,3)=0;
        end
    end
end
imwrite(test2,"hw_1_2_3.jpg");%输出化为"黑白格"的图像