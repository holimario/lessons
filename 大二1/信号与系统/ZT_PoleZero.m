clear all;
close all;
a=0.5;
h=[];  
pha=-pi:pi/100:pi;
xx=cos(pha);
yy=sin(pha);  %build the unit circle
figure(1);

N=40;


for k=1:(2*N+1)
    w=-pi+(k-1)*pi/N;  %frequency w between -pi and +pi
    z=cos(w)+j*sin(w);
    num=z;    %numerator
    den=z-a;  %denominator
    subplot(2,2,1);
   set(gca,'position',[0.3 0.48 0.4 0.5]);  %set the plot position in the figure window
    plot(xx,yy,'k','LineWidth',1);  %plot the unit circle
       hold on;
    text(-1.1,1.1,'Unit Circle'); 
   quiver(-1,1,0.3,-0.3,'k','LineWidth',0.5); 
   
    if w<0
       w1=w+2*pi;
    else
        w1=w;
    end
    plot(0.2*cos(0:pi/100:w1),0.2*sin(0:pi/100:w1),'m','LineWidth',1);
    text(0.2*cos(w1),0.2*sin(w1),'\color{magenta}\omega');   %plot the frequency change 
    
    
    plot([0],[0],'ro','LineWidth',2)   %plot the zero
    plot([a],[0],'bx','LineWidth',2)   %plot the pole
    plot(zeros(size(-1.2:0.01:1.2)),-1.2:0.01:1.2,'k','LineWidth',0.5);   %plot y axis 
    plot(-1.2:0.01:1.2,zeros(size(-1.2:0.01:1.2)),'k','LineWidth',0.5);   %plot x axis
    quiver(0,0,real(num),imag(num),'r','LineWidth',2,'MaxHeadSize',0.7,'AutoScale','off');  %plot the numerator vector
    quiver(a,0,real(den),imag(den),'b','LineWidth',1,'MaxHeadSize',0.7,'AutoScale','off');  %plot the denominator vector
    text(1,0.2,'\slRe');    %label x axis
    text(0.05,1.1,'\slIm'); %lable y axis
    text(0.6,1,'\itz\rm-plane'); 
    axis([-1.2 1.2 -1.2 1.2]); %set the axis range to be displayed
    hold off;
  
    
    ww=[1:k]*pi/N-pi-pi/N;  %phase
    h=[h num/den];    %update the frequency response
    absh=abs(h);      %magnitude response
    phah=angle(h);    %phase response
    subplot(2,2,3);
    set(gca,'position',[0.05 0.02 0.4 0.4]);
    plot(ww,absh,'k','LineWidth',2);
    hold on;
    plot(-1.2*pi:pi/100:1.2*pi,zeros(size(-1.2*pi:pi/100:1.2*pi)),'k','LineWidth',0.5); %plot x axis
    plot(zeros(size(-0.3:0.01:2.4)),-0.3:0.01:2.4,'k','LineWidth',0.5); %plot y axis
    text(-pi,-0.1,'-\pi'); % mark x axis scale
    text(pi,-0.1,'\pi');
    text(0,-0.1,'0');
    text(pi+0.2,0.2,'\omega');
    text(0.2,2.2,'|H(e^j^\omega)|');  %label y axis
    set(gca,'xtick',[],'xticklabel',[])  %remove original axis scale
    hold off;
    axis([-1.2*pi 1.2*pi -0.3 2*1.2]); %set the axis range to be displayed
    
    subplot(2,2,4);
    set(gca,'position',[0.55 0.02 0.4 0.4]);
    plot(ww,phah,'k','LineWidth',2);
    hold on;
    axis([-1.2*pi 1.2*pi -1.2*0.5*pi 1.3*0.5*pi]); %set the axis range to be displayed
    plot(-1.2*pi:pi/100:1.2*pi,zeros(size(-1.2*pi:pi/100:1.2*pi)),'k','LineWidth',0.5); %plot x axis
    plot(zeros(size(-1.2*0.5*pi:pi/100:1.3*0.5*pi)),-1.2*0.5*pi:pi/100:1.3*0.5*pi,'k','LineWidth',0.5);  %plot y axis
    text(-pi,-0.1,'-\pi'); %make x axis scale
    text(pi,-0.1,'\pi');
    text(pi+0.2,0.2,'\omega');
    text(0,-0.1,'0');
    text(0.2,0.65*pi-0.2,'\phi(H(e^j^\omega))');  %label y axis
    line([0,0.1],[pi/2,pi/2],'LineWidth',0.5,'color','k'); % x axis scale
    text(-0.9,pi/2,'\pi/2');
    line([0,0.1],[-pi/2,-pi/2],'LineWidth',0.5,'color','k'); % x axis scale
    text(-1.0,-pi/2,'-\pi/2');
    set(gca,'xtick',[],'xticklabel',[])
    set(gca,'ytick',[],'yticklabel',[])  %remove the original scale
    hold off;
   F=getframe(gcf);   %capture picture frame from figure window
  imind=frame2im(F);
    [imind,cm] = rgb2ind(imind,256);
   %m(k)=getframe;
    if k == 1
        imwrite(imind,cm,'test.gif','GIF', 'Loopcount',inf,'DelayTime',0.2); 
    else
        imwrite(imind,cm,'test.gif','GIF','WriteMode','append','DelayTime',0.2); %build the GIF file
    end  
end
%figure(2);
%set(gca,'looseInset',[0 0 0 0])
%    set(gca,'xtick',[],'xticklabel',[])
%    set(gca,'ytick',[],'yticklabel',[])
%movie(m,5)%重复3次播放动画

    
    