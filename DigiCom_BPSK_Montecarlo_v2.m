%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Subject: Digital Communications
% Lecturer: Sang-Hyo Kim 
%
% Topic: BPSK Modulation Monte Carlo Simulation with Increasing SNR
% version: 2.0 
% data of release: April 30, 2023 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc; 
close all; 
clear; 

% Parameters
N = 40; % number of symbols in a transmission (block size)
SNR_dB = 0:1:12; % SNR range in dB (here SNR = Eb/No) 
numIter = 30000; % number of Monte Carlo iterations
ber = zeros(1, length(SNR_dB)); % bit error rate


%
% one time transmission and reception and plot
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t_snr_db = 3; 
snr = 10^(t_snr_db/ 10); % linear SNR is calculated 
figure(1); 
data = randi([0, 1], 1, N);
bpsk = (1 - 2 * data) + 1j * zeros(1, N); % Eb = 1.0 

% AWGN channel
noise = (1/sqrt(2)) * (randn(1, N) + 1j * randn(1, N));
rx_signal = bpsk + noise/sqrt(snr);

% plotting 
plot(complex(bpsk),'bo');
title('Constellation, Tx signal, and Rx signal'); 
xlabel('real')
ylabel('imaginary')
grid on; 
hold on; 
plot(rx_signal,'r*'); 
 
axis([-3,3,-2,2])
rx_signal_real_projection = real(rx_signal); 
plot(complex(rx_signal_real_projection),'g.'); 
legend('Transmitted (x)','Received (y=x+z)','Received (real only)')

% Draw the real and imaginary axes
line([0 0], ylim, 'Color', 'k', 'LineWidth', 0.5, 'HandleVisibility', 'off')
line(xlim, [0 0], 'Color', 'k', 'LineWidth', 0.5, 'HandleVisibility', 'off')



% return % 


%
% BPSK transmission and reception (Monte-Carlo simulation) 
% 
% Loop over SNR values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i = 1:length(SNR_dB)
    % Convert SNR from dB to linear scale
    snr = 10^(SNR_dB(i) / 10);

    % Monte Carlo loop
    for iter = 1:numIter
        % Generate random binary data
        data = randi([0, 1], 1, N);
        
        % BPSK modulation
        bpsk = (1 - 2 * data) + 1j * zeros(1, N);
        
        % AWGN channel
        noise = (1/sqrt(2)) * (randn(1, N) + 1j * randn(1, N));
        rx_signal = bpsk + noise/sqrt(snr);
        
        % BPSK demodulation
        rx_data = real(rx_signal) < 0;
        
        % Error count
        errors = sum(data ~= rx_data); % counting mismatches  
        ber(i) = ber(i) + errors;
    end
end

% Average BER over iterations
ber = ber / (N * numIter);

% Plot BER vs SNR
figure(2); % new figure 
semilogy(SNR_dB, ber, 'ro--', 'LineWidth', 1.0);
grid on;
xlabel('SNR (Eb/No in dB)');
ylabel('BER (Bit Error Rate)');
title('BPSK Modulation: BER vs SNR');
legend('Monte Carlo');


% analytic results 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hold on; 
SNR_linear =  10.^(SNR_dB/10); 
semilogy(SNR_dB,qfunc(sqrt(SNR_linear*2)),'b-','LineWidth',1.0,'DisplayName','Analysis')
%legend('Analysis')

