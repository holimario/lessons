open_system('myexp7_3.slx');
SNR_list = linspace(-10, 10, 11); % in dB
ser_rc = zeros(1, length(SNR_list));
ser_th = zeros(1, length(SNR_list));

for i = 1:length(SNR_list)
    SNR = SNR_list(i); % in dB
    simOut = sim('myexp7_3');
    ser_rc(i) = simOut.ser(1);
    ser_th(i) = qfunc(sqrt(2*10^(SNR/10)));% TODO
end
save_system;
close_system;
%% SER Curve
semilogy(SNR_list, ser_rc,'*'); hold on;
semilogy(SNR_list, ser_th,'--'); hold on;
ylim([1e-5 1]);
xlabel('Signal to Noise Ratio E_b/n_0 (dB)');
ylabel('SER');
legend('Raised Cosine PAM w/ Optimal Receiver', 'Theoretical', 'Location','northeast');
grid on;