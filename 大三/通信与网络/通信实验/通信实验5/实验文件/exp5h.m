%% Repetition Code
open_system('myexp5_3.slx');
n_list = [3 4 5];
eprob_list = logspace(-3,-0.5,10);
ber_rep = zeros(length(n_list), length(eprob_list));
ber_rep_th = zeros(length(n_list), length(eprob_list));

for i = 1:length(n_list)
    for j = 1:length(eprob_list)
        M = n_list(i);  
        n = 2^M - 1;
        eprob = eprob_list(j);
        simOut = sim('myexp5_3');
        ber_rep(i,j) = simOut.ErrorStat(1);
        ber_rep_th(i,j) = 3/n*nchoosek(n,2)*eprob^(2);
    end
end
save_system;
close_system;
%% BER Curve
loglog([eprob_list(1) 1],[eprob_list(1) 1],'k--'); hold on;
c = eye(3);
for i = 1:length(n_list)
    loglog(eprob_list, ber_rep(i,:),'*','Color',c(i,:));
    loglog(eprob_list, ber_rep_th(i,:),'Color',c(i,:));
end
ylim([1e-5 1]);
xlabel('Channel Error Probability');
ylabel('BER');
grid on;
legend('No Coding', '[7,4] Hamming Simulation', '[7,4] Hamming Theoretical', ...
    '[15,11] Hamming Simulation', '[15,11] Hamming Theoretical', ...
    '[31,26] Hamming Simulation', '[31,26] Hamming Theoretical', ...
    'Location','southeast');