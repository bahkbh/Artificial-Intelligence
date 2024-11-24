
% BPSK plot 
% parameters
Es_N0_dB = 0:10; % range of Es/N0 values in dB
Es_N0 = 10.^(Es_N0_dB/10); % convert Es/N0 from dB to linear scale
point=0.01*[7.83, 5.69, 3.7, 2.27, 1.23, 0.62, 0.22, 0.071, 0.02, 3.37*10^(-3), 3.39*10^(-4)];
% calculating BER
ber = qfunc(sqrt(2*Es_N0));
ch_CER=0.01*[17.64,9.6,4.44,1.68,0.56,0.12, 0.02,0.004,0,0,0];
coded_CER= 0.01*[10.06, 5.5, 2.6, 1.02, 0.31, 0.07, 0.01, 0.001, 8.4*10^(-5), 2.2*10^(-6), 4.4*10^(-8)];
% plot
semilogy(Es_N0_dB,coded_CER, 'bo-',Es_N0_dB,ch_CER, 'ro-');
legend('계산 Coded CER', '측정 Coded CER');
grid on;
xlabel('Es/N0 (dB)');
ylabel('Code Error Rate');
title('계산 Coded CER VS 측정 Coded CER');




