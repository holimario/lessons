function varargout = homework(varargin)
% HOMEWORK MATLAB code for homework.fig
%      HOMEWORK, by itself, creates a new HOMEWORK or raises the existing
%      singleton*.
%
%      H = HOMEWORK returns the handle to a new HOMEWORK or the handle to
%      the existing singleton*.
%
%      HOMEWORK('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in HOMEWORK.M with the given input arguments.
%
%      HOMEWORK('Property','Value',...) creates a new HOMEWORK or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before homework_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to homework_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help homework

% Last Modified by GUIDE v2.5 17-Jan-2021 21:28:20

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @homework_OpeningFcn, ...
                   'gui_OutputFcn',  @homework_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before homework is made visible.
function homework_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to homework (see VARARGIN)

% Choose default command line output for homework
handles.output = hObject;

% Update handles structure


% UIWAIT makes homework wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = homework_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
global pw sw cw str x y p sp a;
pw=0;
sw=0;
cw=0;
str=0;
x=0;
y=0;
p=0;
sp=0;
a=0;

% --- Executes on button press in b2.
function b1_Callback(hObject, eventdata, handles)
% hObject    handle to b2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
pw=str2num(get(handles.e1,'String'))*1000000;
sw=str2num(get(handles.e2,'String'))*1000000;
p=str2num(get(handles.e3,'String'));
sp=str2num(get(handles.e4,'String'));
a=10^(str2num(get(handles.e5,'String'))./20);
pp=get(handles.s1,'Value');
gg=get(handles.s2,'Value');
disp(pp);

x=round((log((10^(p./10)-1)/(10^(sp./10)-1))./log(pw./sw))./2);
cw=round((10^(sp./10)-1)^(-1./(2*x))*2*pi*sw);
num=[];
den=[];
syms s;
for t=1:100
    den=[den;cw*exp(1i*(pi/2+pi./(2*x)+(t-1)*pi./x))];
    if t==x
        break;
    end
end
sys=zpk(num,den,a*cw^x);
str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'元件数据为：'];
if(x>8)
    msgbox('本程序仅进行阶数不大于8的运算。');
else
    if(x<=0)
        msgbox('输入有误，请检查。');
    else
        set(handles.e1,'Visible','off');
        set(handles.e2,'Visible','off');
        set(handles.e3,'Visible','off');
        set(handles.e4,'Visible','off');
        set(handles.e5,'Visible','off');
        set(handles.t1,'Visible','off');
        set(handles.t2,'Visible','off');
        set(handles.t3,'Visible','off');
        set(handles.t4,'Visible','off');
        set(handles.t5,'Visible','off');
        set(handles.t6,'Visible','off');
        set(handles.t7,'Visible','off');
        set(handles.t8,'Visible','off');
        set(handles.t9,'Visible','off');
        set(handles.t10,'Visible','off');
        set(handles.t17,'Visible','off');
        set(handles.t18,'Visible','off');
        set(handles.t12,'Visible','on');
        set(handles.t13,'Visible','on');
        set(handles.t14,'Visible','on');
        set(handles.t15,'Visible','on');
        set(handles.t16,'Visible','on');
        set(handles.t11,'visible','on');
        set(handles.b1,'Visible','off');
        set(handles.s1,'Visible','off');
        set(handles.s2,'Visible','off');
        set(handles.p1,'Visible','on');
        set(handles.p2,'Visible','on');
        set(handles.p3,'Visible','on');
        set(handles.p4,'Visible','on');
        set(handles.p5,'Visible','on');
        set(handles.b2,'Visible','on');
      if pp==1
          axes(handles.p1);
        theta=0:pi/100:2*pi;
        u=cw*cos(theta); l=cw*sin(theta);
        plot(u,l,'--')
        hold on
        grid on
        for p=1:10
            plot(cw*real(exp(1i*(pi/2+pi./(2*x)+(p-1)*pi./x))),cw*imag(exp(1i*(pi/2+pi./(2*x)+(p-1)*pi./x))),'x')
            if p==x
                break;
            end
        end
        hold off
        w=logspace(0,9,2000);
        axes(handles.p2);
        bode(sys,w);
        grid on
        axes(handles.p3);
        t=[0:0.0000000001:0.00001];
        impulse(sys,t);
        grid on
        axes(handles.p4);
        step(sys);
        grid on
        if gg==1
            switch x
                case 1
                    im=imread('d1.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R2=1000kΩ,','R3=1000kΩ,','C1=10pF,','R4=100kΩ,','R5=',num2str(a./2*100),'kΩ'];
                case 2
                    im=imread('d2.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str((sin(pi/4)./(10^(-11)*cw*1000))./2),'kΩ,','R2=',num2str((sin(pi/4)./(10^(-11)*cw*1000))./2),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(pi/4)./(10^(-11)*cw))./2)^2)),'pF,','R3=100kΩ,','R4=',num2str(a.*100),'kΩ'];
                case 3
                    im=imread('d3.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R2=1000kΩ,','R3=1000kΩ,','C1=10pF,','R4=',num2str((1/(10^(-11)*cw*1000))./2),'kΩ,','R5=',num2str((1/(10^(-11)*cw*1000))./2),'kΩ，','C2=10pF,','C3=',num2str(1./(cw^2*10*10^(-24)*((1/(10^(-11)*cw))./2)^2)),'pF,','R6=100kΩ,','R7=',num2str(a./2*100),'kΩ'];
                case 4
                    im=imread('d4.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str((sin(pi/8)./(10^(-12)*cw*1000))./2),'kΩ,','R2=',num2str((sin(pi/8)./(10^(-12)*cw*1000))./2),'kΩ','C4=100pF,','C2=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/8)./(10^(-11)*cw))./2)^2)),'pF,','R3=',num2str((sin(3*pi/8)./(10^(-11)*cw*1000))./2),'kΩ,','R4=',num2str((sin(3*pi/8)./(10^(-11)*cw*1000))./2),'kΩ,','C2=10pF,','C3=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/8)./(10^(-11)*cw))./2)^2)),'pF,','R5=100kΩ,','R6=',num2str(a*100),'kΩ'];
                case 5
                    im=imread('d5.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R2=1000kΩ,','R3=1000kΩ,','C1=10pF,','R4=',num2str((sin(pi/10)./(10^(-10)*cw*1000))./2),'kΩ,','R5=',num2str((sin(pi/10)./(10^(-10)*cw*1000))./2),'kΩ,','C4=100pF,','C5=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/10)./(10^(-11)*cw))./2)^2)),'pF,','R6=',num2str((sin(3*pi/10)./(10^(-11)*cw*1000))./2),'kΩ,','R7=',num2str((sin(3*pi/10)./(10^(-11)*cw*1000))./2),'kΩ,','C2=10pF,','C3=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/10)./(10^(-11)*cw))./2)^2)),'pF,','R8=100kΩ,','R9=',num2str(a./2*100),'kΩ'];
                case 6
                    im=imread('d6.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str((sin(pi/12)./(10^(-10)*cw*1000))./2),'kΩ,','R2=',num2str((sin(pi/10)./(10^(-12)*cw*1000))./2),'kΩ','C6=100pF,','C7=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/12)./(10^(-11)*cw))./2)^2)),'pF,','R3=',num2str((sin(3*pi/12)./(10^(-11)*cw*1000))./2),'kΩ,','R4=',num2str((sin(3*pi/12)./(10^(-11)*cw*1000))./2),'kΩ,','C4=10pF,','C5=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/12)./(10^(-11)*cw))./2)^2)),'pF,','R5=',num2str((sin(5*pi/12)./(10^(-11)*cw*1000))./2),'kΩ,','R6=',num2str((sin(5*pi/12)./(10^(-11)*cw*1000))./2),'kΩ','C2=10pF,','C3=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/12)./(10^(-11)*cw))./2)^2)),'pF,','R4=100kΩ,','R5=',num2str(a*100),'kΩ'];
                case 7
                    im=imread('d7.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R2=1000kΩ,','R3=1000kΩ,','C1=10pF,','R4=',num2str((sin(pi/14)./(10^(-10)*cw*1000))./2),'kΩ,','R5=',num2str((sin(pi/14)./(10^(-10)*cw*1000))./2),'kΩ','C6=100pF,','C7=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/14)./(10^(-11)*cw))./2)^2)),'pF,','R6=',num2str((sin(3*pi/14)./(10^(-11)*cw*1000))./2),'kΩ,','R7=',num2str((sin(3*pi/14)./(10^(-11)*cw*1000))./2),'kΩ','C4=10pF,','C5=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/14)./(10^(-11)*cw))./2)^2)),'pF,','R8=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./2),'kΩ,','R9=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./2),'kΩ','C2=10pF,','C3=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/14)./(10^(-11)*cw))./2)^2)),'pF,','R10=100kΩ,','R11=',num2str(a./2*100),'kΩ'];
                case 8
                    im=imread('d8.png');
                    axes(handles.p5)
                    imshow(im)
                    str=[str,10,'R1=',num2str((sin(pi/16)./(10^(-10)*cw*1000))./2),'kΩ,','R2=',num2str((sin(pi/16)./(10^(-10)*cw*1000))./2),'kΩ','C1=100pF,','C2=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/16)./(10^(-11)*cw))./2)^2)),'pF,','R3=',num2str((sin(3*pi/16)./(10^(-11)*cw*1000))./2),'kΩ,','R4=',num2str((sin(3*pi/16)./(10^(-11)*cw*1000))./2),'kΩ','C3=10pF,','C4=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/16)./(10^(-11)*cw))./2)^2)),'pF,','R5=',num2str((sin(5*pi/16)./(10^(-11)*cw*1000))./2),'kΩ,','R6=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./2),'kΩ','C5=10pF,','C6=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/16)./(10^(-11)*cw))./2)^2)),'pF,','R7=',num2str((sin(7*pi/16)./(10^(-11)*cw*1000))./2),'kΩ,','R8=',num2str((sin(7*pi/16)./(10^(-11)*cw*1000))./2),'kΩ','C7=10pF,','C8=',num2str(1./(cw^2*10*10^(-24)*((sin(7*pi/16)./(10^(-11)*cw))./2)^2)),'pF,','R9=100kΩ,','R10=',num2str(a*100),'kΩ'];
            end
        else
            if gg==2
                
                switch x
                    case 1
                        im=imread('m1.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R1=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R2=1000kΩ,','R3=1000kΩ,','C1=10pF,','R4=100kΩ,','R5=',num2str(a./2*100),'kΩ'];
                    case 2
                        im=imread('m2.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R1=',num2str((sin(pi/4)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(pi/4)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(pi/4)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(pi/4)./(10^(-11)*cw))./3)^2)),'pF,','R9=100kΩ,','R10=',num2str(a*100),'kΩ'];
                    case 3
                        im=imread('m3.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R6=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R7=1000kΩ,','R8=1000kΩ,','C3=10pF,','R1=',num2str((sin(pi/6)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(pi/6)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(pi/6)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(pi/6)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a./2*100),'kΩ'];
                    case 4
                        im=imread('m4.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R6=',num2str((sin(pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','R8=',num2str((sin(pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','R7=',num2str((sin(pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','C3=10pF,','C4=',num2str(1./(cw^2*10*10^(-24)*((sin(pi/8)./(10^(-11)*cw))./3)^2)),'pF,','R1=',num2str((sin(3*pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(3*pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(3*pi/8)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/8)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a*100),'kΩ'];
                    case 5
                        im=imread('m5.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R9=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R10=1000kΩ,','R11=1000kΩ,','C5=10pF,','R6=',num2str((sin(pi/10)./(10^(-10)*cw*1000))./3),'kΩ,','R8=',num2str((sin(pi/10)./(10^(-10)*cw*1000))./3),'kΩ,','R7=',num2str((sin(pi/10)./(10^(-10)*cw*1000))./3),'kΩ,','C3=100pF,','C4=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/10)./(10^(-11)*cw))./3)^2)),'pF,','R1=',num2str((sin(3*pi/10)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(3*pi/10)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(3*pi/10)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/10)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a./2*100),'kΩ'];
                    case 6
                        im=imread('m6.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R11=',num2str((sin(pi/12)./(10^(-10)*cw*1000))./3),'kΩ,','R9=',num2str((sin(pi/12)./(10^(-10)*cw*1000))./3),'kΩ,','R10=',num2str((sin(pi/12)./(10^(-10)*cw*1000))./3),'kΩ,','C5=100pF,','C6=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/12)./(10^(-11)*cw))./3)^2)),'pF,','R6=',num2str((sin(3*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','R8=',num2str((sin(3*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','R7=',num2str((sin(3*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','C3=10pF,','C4=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/12)./(10^(-11)*cw))./3)^2)),'pF,','R1=',num2str((sin(5*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(5*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(5*pi/12)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/12)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a*100),'kΩ'];
                    case 7
                        im=imread('m7.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R12=',num2str(1./(10*10^(-12)*cw*1000)),'kΩ,','R13=1000kΩ,','R14=1000kΩ,','C7=10pF,','R11=',num2str((sin(pi/14)./(10^(-10)*cw*1000))./3),'kΩ,','R9=',num2str((sin(pi/14)./(10^(-10)*cw*1000))./3),'kΩ,','R10=',num2str((sin(pi/14)./(10^(-10)*cw*1000))./3),'kΩ,','C5=100pF,','C6=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/10)./(10^(-11)*cw))./3)^2)),'pF,','R1=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(5*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C4=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/14)./(10^(-11)*cw))./3)^2)),'pF,','R6=',num2str((sin(3*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','R8=',num2str((sin(3*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','R7=',num2str((sin(3*pi/14)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/14)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a./2*100),'kΩ'];
                    case 8
                        im=imread('m8.png');
                        axes(handles.p5)
                        imshow(im)
                        str=[str,10,'R14=',num2str((sin(pi/16)./(10^(-10)*cw*1000))./3),'kΩ,','R12=',num2str((sin(pi/16)./(10^(-10)*cw*1000))./3),'kΩ,','R13=',num2str((sin(pi/16)./(10^(-10)*cw*1000))./3),'kΩ,','C7=100pF,','C8=',num2str(1./(cw^2*100*10^(-24)*((sin(pi/16)./(10^(-11)*cw))./3)^2)),'pF,','R11=',num2str((sin(3*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R9=',num2str((sin(3*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R10=',num2str((sin(3*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','C5=10pF,','C6=',num2str(1./(cw^2*10*10^(-24)*((sin(3*pi/16)./(10^(-11)*cw))./3)^2)),'pF,','R6=',num2str((sin(5*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R8=',num2str((sin(5*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R7=',num2str((sin(5*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','C3=10pF,','C4=',num2str(1./(cw^2*10*10^(-24)*((sin(5*pi/16)./(10^(-11)*cw))./3)^2)),'pF,','R1=',num2str((sin(7*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R2=',num2str((sin(7*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','R3=',num2str((sin(7*pi/16)./(10^(-11)*cw*1000))./3),'kΩ,','C1=10pF,','C2=',num2str(1./(cw^2*10*10^(-24)*((sin(7*pi/16)./(10^(-11)*cw))./3)^2)),'pF,','R4=100kΩ,','R5=',num2str(a*100),'kΩ'];
                end
            end
        end
      else
          if pp==2
        cw=round((10^(sp./10)-1)^(1./(2*x))*2*pi*pw);
        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'元件数据为：'];
        num=[];
        den=[];
        syms s;
for t=1:100
    num=[num,0];
    den=[den;cw*(-1)./exp(1i*(pi/2+pi./(2*x)+(t-1)*pi./x))];
    if t==x
        break;
    end
end
        sys=zpk(num,den,a);
        axes(handles.p1);
        theta=0:pi/100:2*pi;
        u=cw*cos(theta); l=cw*sin(theta);
        plot(u,l,'--')
        hold on
        plot(0,0,'o');
        grid on
        for p=1:10
            plot(real(cw./exp(1i*(pi/2+pi./(2*x)+(p-1)*pi./x))),imag(cw./exp(1i*(pi/2+pi./(2*x)+(p-1)*pi./x))),'x')
            if p==x
                break;
            end
        end
        hold off
        w=logspace(0,9,2000);
        axes(handles.p2);
        bode(sys,w);
        grid on
        axes(handles.p3);
        t= 0:0.000000001:0.000005 ;
        impulse(sys,t);
        grid on
        axes(handles.p4);
        step(sys);
        grid on
              if gg==1
                  switch x
                case 1
                    im=imread('s1.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                case 2
                    im=imread('s2.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                case 3
                    im=imread('s3.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];                
                      case 4
                    im=imread('s4.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];                
                      case 5
                    im=imread('s5.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];                
                      case 6
                    im=imread('s6.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                case 7
                    im=imread('s7.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                case 8
                    im=imread('s8.png');
                    axes(handles.p5)
                    imshow(im)
                    str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                  end
              else
                  if gg==2
                      switch x
                    case 1
                        im=imread('g1.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 2
                        im=imread('g2.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 3
                        im=imread('g3.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 4
                        im=imread('g4.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 5
                        im=imread('g5.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 6
                        im=imread('g6.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 7
                        im=imread('g7.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                    case 8
                        im=imread('g8.png');
                        axes(handles.p5)
                        imshow(im)
                        str=['巴特沃斯滤波器的阶数为',num2str(x),10,'截止频率为',num2str(cw),'rad/s',10,'高通滤波器尚未处理完元件参数的确定QwQ，电路图如上'];
                  end
              end
              end
          end
      end
    set(handles.t11,'String',str);
  end
end



% --- Executes during object creation, after setting all properties.
function b1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% --- Executes on selection change in s1.
function s1_Callback(hObject, eventdata, handles)
% hObject    handle to s1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% Hints: contents = cellstr(get(hObject,'String')) returns s1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from s1


% --- Executes during object creation, after setting all properties.
function s1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to s1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function e1_Callback(hObject, eventdata, handles)
% hObject    handle to e1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of e1 as text
%        str2double(get(hObject,'String')) returns contents of e1 as a double


% --- Executes during object creation, after setting all properties.
function e1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to e1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function e3_Callback(hObject, eventdata, handles)
% hObject    handle to e3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of e3 as text
%        str2double(get(hObject,'String')) returns contents of e3 as a double


% --- Executes during object creation, after setting all properties.
function e3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to e3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function e4_Callback(hObject, eventdata, handles)
% hObject    handle to e4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of e4 as text
%        str2double(get(hObject,'String')) returns contents of e4 as a double


% --- Executes during object creation, after setting all properties.
function e4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to e4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function e5_Callback(hObject, eventdata, handles)
% hObject    handle to e5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of e5 as text
%        str2double(get(hObject,'String')) returns contents of e5 as a double


% --- Executes during object creation, after setting all properties.
function e5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to e5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function e2_Callback(hObject, eventdata, handles)
% hObject    handle to e2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of e2 as text
%        str2double(get(hObject,'String')) returns contents of e2 as a double


% --- Executes during object creation, after setting all properties.
function e2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to e2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in s2.
function s2_Callback(hObject, eventdata, handles)
% hObject    handle to s2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns s2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from s2


% --- Executes during object creation, after setting all properties.
function s2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to s2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function p1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to p1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% Hint: place code in OpeningFcn to populate p1


% --- Executes on button press in b2.
function b2_Callback(hObject, eventdata, handles)
% hObject    handle to b2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.e1,'visible','on');
set(handles.e2,'visible','on');
set(handles.e3,'visible','on');
set(handles.e4,'visible','on');
set(handles.e5,'visible','on');
set(handles.t1,'visible','on');
set(handles.t2,'visible','on');
set(handles.t3,'visible','on');
set(handles.t4,'visible','on');
set(handles.t5,'visible','on');
set(handles.t6,'visible','on');
set(handles.t7,'visible','on');
set(handles.t8,'visible','on');
set(handles.t9,'visible','on');
set(handles.t10,'visible','on');
set(handles.t17,'Visible','on');
set(handles.t18,'Visible','on');
set(handles.t12,'Visible','off');
set(handles.t13,'Visible','off');
set(handles.t14,'Visible','off');
set(handles.t15,'Visible','off');
set(handles.t16,'Visible','off');
set(handles.t11,'visible','off');
set(handles.b1,'visible','on');
set(handles.s1,'visible','on');
set(handles.s2,'visible','on');
cla(handles.p1,'reset');
cla(handles.p2,'reset');
cla(handles.p3,'reset');
cla(handles.p4,'reset');
cla(handles.p5,'reset');
set(handles.p1,'visible','off');
set(handles.p2,'visible','off');
set(handles.p3,'visible','off');
set(handles.p4,'visible','off');
set(handles.p5,'visible','off');
set(handles.b2,'visible','off');


% --- Executes during object creation, after setting all properties.
function b2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called



% --- Executes during object creation, after setting all properties.
function a2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to a2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over b1.
function b1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to b1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function text13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes during object creation, after setting all properties.
function t11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to t11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
