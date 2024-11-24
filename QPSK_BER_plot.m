
% QPSK plot 
% parameters
Es_N0_dB = 0:10; % range of Es/N0 values in dB
Es_N0 = 10.^(Es_N0_dB/10); % convert Es/N0 from dB to linear scale

% calculating BER
ber =qfunc(sqrt(Es_N0));

% plot
semilogy(Es_N0_dB, ber, 'bo-');
grid on;
xlabel('Es/N0 (dB)');
ylabel('Bit Error Rate');
title('Theoretical BER performance of QPSK in AWGN');



