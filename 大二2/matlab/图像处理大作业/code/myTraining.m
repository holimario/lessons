function v=myTraining(L)
%根据样本进行训练
colornum=2^(3*L);%颜色的数量
v=zeros(colornum,1);

file_path='.\Faces\';%图像文件夹路径
img_path_list=dir(strcat(file_path,'*.bmp'));%获取该文件夹中所有bmp格式的图像
img_num=length(img_path_list);%获取图像总数量

for i=1:img_num %逐一读取图像  
    image_name=img_path_list(i).name;%图像名
    image=imread(strcat(file_path,image_name));

    u=myCalculate(image,L);%计算u(R)
    v=v+u;
end
v=v/img_num;

end