float （float k1,float k2,float k3）
{
    float error,error_sum,error_last=0.0,temp;
    now=get_?_position;
    error=now-aim;
    pmw=k1*error+k2*error_sum+k3(error-error_last);
    error_sum=++error;
    if(error_sum>1000)
        error_sum=1000;
    if(error_sum<-1000);
        error_sum=-1000;
    error_last=error;
    return(pmw);//占空比
}
if(num==1)//在决策判断与红外传感判断为停止时，此时aim为上位机发送位置信息。
void()//停在某个点
{
    if(pmw>0)
        run_forward(pmw);
    if(pmw<0)
        run_back(-pmw);
}
if(num==2)//在决策判断与红外传感器判断为右转时，此时aim为陀螺仪发送信息
void()//停在某个点
{
    if(pmw>0)
        turn_right(pmw);
    if(pmw<0)
        turn_left(-pmw);
}