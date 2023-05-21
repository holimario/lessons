function []=my_wavread()
load('Guitar.MAT');
[a,fs]=audioread('fmt.wav');
sound(a,fs);
plot(a);
end

