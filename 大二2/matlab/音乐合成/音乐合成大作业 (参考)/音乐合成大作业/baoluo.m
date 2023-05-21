function R = baoluo(m,t)
k=2*pi;
lt=length(t)-1;
M=zeros(1,length(t));
T=t(end);
M(1:lt*0.3)=k*t(1:lt*0.3).*exp(-k*t(1:lt*0.3)/T);
M(lt*0.3+1:lt*0.8)=M(lt*0.3);
M(lt*0.8:end)=5*M(lt*0.8).*(-1/T*t(lt*0.8:end)+1);
R=M.*m/T;
end

