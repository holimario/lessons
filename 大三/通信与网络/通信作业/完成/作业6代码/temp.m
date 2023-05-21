syms w;
% w = -10:0.01:10;
fw = sinc(w)^2;
ft = ifourier(fw);
% figure(1);
% plot(w,fw);
%figure()
t = -0.1:0.00001:0.1;
ht = sin(60*pi*t).^2./(20*pi^2*t.^2);
figure(1);
plot(t,ht);

[t,omg,FT,IFT] = prefourier([-1,1],5000,[-400,400],500);
f = sin(60*pi*t).^2./(20*pi^2*t.^2);
f(2501) = f(2500);
% f = heaviside(t+0.5)-heaviside(t-0.5);
F = FT*f;
figure(2);
plot(omg,abs(F));

[t,omg,FT,IFT] = prefourier([-0.2,0.2],5000,[-400,400],5000);
G = sqrt((3*(1-abs(omg)/(60*2*pi))).*(heaviside(t+60*2*pi)-heaviside(t-60*2*pi)));
g = IFT*G;
figure(3);
plot(t,g);