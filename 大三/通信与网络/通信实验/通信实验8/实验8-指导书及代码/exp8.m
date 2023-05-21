open_system('myexp8_2.slx');
k_list = [2 4 6];
M_list = [4 16 64];
SNR_list = linspace(-5, 15, 11); % in dB
ber_psk = zeros(length(k_list), length(SNR_list));
ber_psk_th = zeros(length(k_list), length(SNR_list));
ber_qam = zeros(length(k_list), length(SNR_list));
ber_qam_th = zeros(length(k_list), length(SNR_list));

for i = 1:length(k_list)
    for j = 1:length(SNR_list)
        k = k_list(i);
        M = M_list(i);
        SNR = SNR_list(j); % in dB
        simOut = sim('myexp8_2');
        ber_psk(i,j) = simOut.ber_psk(1);
        ber_qam(i,j) = simOut.ber_qam(1);
        SNR_mag = 10^(SNR/10);
        ber_psk_th(i,j) = 2/log2(M)*...
            qfunc(sin(pi/M)*sqrt(2*log2(M)*SNR_mag));% TODO
        ber_qam_th(i,j) = 4/log2(M)*(1-1/sqrt(M))*...
            qfunc(sqrt(3*log2(M)/(M-1)*SNR_mag));% TODO
    end
end
save_system;
close_system;
%% SER & BER Curve
c = [0 0 0; 1 0 0; 0 0 1];
figure;
for i = 1:length(k_list)
    semilogy(SNR_list, ber_psk(i,:),'o','Color',c(i,:)); hold on;
    semilogy(SNR_list, ber_psk_th(i,:),'--','Color',c(i,:)); hold on;
    semilogy(SNR_list, ber_qam(i,:),'*','Color',c(i,:)); hold on;
    semilogy(SNR_list, ber_qam_th(i,:),'-','Color',c(i,:)); hold on;
end
ylim([1e-5 1]);
xlabel('Signal to Noise Ratio (E_b/n_0, dB)');
ylabel('BER');
legend('QPSK BER Experiment', 'QPSK BER Theoretical', '4QAM BER Experiment', '4QAM BER Theoretical', ...
    '16PSK BER Experiment', '16PSK BER Theoretical', '16QAM BER Experiment', '16QAM BER Theoretical', ...
    '64PSK BER Experiment', '64PSK BER Theoretical', '64QAM BER Experiment', '64QAM BER Theoretical', ...
    'Location','southwest');
grid on;