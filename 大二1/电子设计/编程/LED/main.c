#include <stdio.h>
#include <stdlib.h>

char direction[30];
void Run()
{
    for(i=0; direction[i]!='\0'; i=i+2)
    {
        if(direction[i]=='L')
        {
            int o,num=0;
            o=(int)direction[i+1]-(int)'0';
            aim1=90+A;
            aim3=o*B;
            float error_sum1=0.0,error_sum2=0.0,now1;
            int error_sum3=0;
            now1=angle();
            for(; now1-aim1>0.5||now1-aim1<-0.5;)
            {
                now1=angle();
                Turn(PIDturn(error_sum1,now1,aim1));
            }
            Bip=0;
            aim2=90+A;
            for(;;)
            {
                now2=angle();
                now3=Bip;
                RunForward(PIDstop(now3,aim3),PIDforward(error_sum2,now2,aim2));
            }
        }
        if(direction[i]=='R')
        {
            int o,num=0;
            o=(int)direction[i+1]-(int)'0';
            aim1=-90+A;
            aim3=o*B;
            float error_sum1=0.0,error_sum2=0.0,now1;
            int error_sum3=0;
            for(; now1-aim1>0.5||now1-aim1<-0.5;)
            {
                now1=angle();
                Turn(PIDturn(error_sum1,now1,aim1));
            }
            bbip=Bip;
            aim2=-90+A;
            for(; num;)
            {
                now2=angle();
                now3=bbip-Bip;
                RunForward(PIDstop(error_sum3,now3,aim3),PIDforward(error_sum2,now2,aim2));
            }
        }
        if(direction[i]=='F')
        {
            int o,num=0;
            o=(int)direction[i+1]-(int)'0';
            aim1=A;
            aim3=o*B;
            float error_sum1=0.0,error_sum2=0.0,now1;
            int error_sum3=0;
            for(; now1-aim1>0.5||now1-aim1<-0.5;)
            {
                now1=angle();
                Turn(PIDturn(error_sum1,now1,aim1));
            }
            bbip=Bip;
            aim2=A;
            for(; num;)
            {
                now2=angle();
                now3=bbip-Bip;
                RunForward(PIDstop(error_sum3,now3,aim3),PIDforward(error_sum2,now2,aim2));
            }
        }
        if(direction[i]=='B')
        {
            int o,num=0;
            o=(int)direction[i+1]-(int)'0';
            aim1=-A;
            aim3=o*B;
            float error_sum1=0.0,error_sum2=0.0,now1;
            int error_sum3=0;
            for(; now1-aim1>0.5||now1-aim1<-0.5;)
            {
                now1=angle();
                Turn(PIDturn(error_sum1,now1,aim1));
            }
            bbip=Bip;
            aim2=-A;
            for(; num;)
            {
                now2=angle();
                now3=bbip-Bip;
                RunForward(PIDstop(error_sum3,now3,aim3),PIDforward(error_sum2,now2,aim2));
            }
        }
        if(direction[i]=='\0')
        {
            StopRightNow();
        }
    }
}

