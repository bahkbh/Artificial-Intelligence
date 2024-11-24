
% 16-QAM plot 
% parameters
Es_N0_dB = 0:10; % range of Es/N0 values in dB
Es_N0 = 10.^(Es_N0_dB/10); % convert Es/N0 from dB to linear scale

% calculating BER
ch_BER=0.01*[4.41,2.4,1.11,0.42,0.14,0.03,4.8*10^(-3),10^(-3),0,0,0];
Coded_BER=0.01*[2.51,1.38,0.65,0.26,0.08,0.02, 2*10^(-3), 2.5*10^(-4),2.1*10^(-5),5.5*10^(-7),1.1*10^(-8)];
% plot
semilogy(Es_N0_dB, Coded_BER, 'bo-',Es_N0_dB, ch_BER, 'ro-');
legend('계산 Coded BER','측정 Coded BER')
grid on;
xlabel('Es/N0 (dB)');
ylabel('Bit Error Rate');
title('계산 Coded BER VS 측정 Coded BER');



