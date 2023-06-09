load('Guitar.MAT');
%{
[a,fs]=audioread('fmt.wav');
sound(a,fs);
%}
%{
figure;
subplot(2,1,1);
plot(realwave);
subplot(2,1,2);
plot(wave2proc);
%}
wave1=zeros(length(realwave),1);
resampledwave=resample(realwave,10,1);
for a=1:1:10
    wave1=wave1+resampledwave((a-1)*length(realwave)+1:a*length(realwave))/10;
end
wavedone=repmat(wave1,10,1);
wavedone=resample(wavedone,1,10);
A=abs(wavedone-wave2proc);
%{
figure;
subplot(3,1,1);
plot(realwave);
subplot(3,1,2);
plot(wave2proc);
subplot(3,1,3);
plot(wavedone);
%}
%{
figure;
hold on;
plot(A);
%}