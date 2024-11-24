clear all; 
close all;

% Set parameters
carrier_frequency = 1000;         % Set carrier frequency
sampling_frequency = 100000;      % Set sampling frequency
sample_count = 5000;              % Set number of samples
modulating_frequency = 1000;      % Set modulating frequency
modulation_index = 0.0628;        % Set modulation index

% Set higher gains for faster tracking
proportional_gain = 1;           % Set proportional gain for the loop filter
integral_gain = 0.1;                % Set integral gain for the loop filter

% Generate time vector
sampling_period = 1 / sampling_frequency; 
time = (0:sample_count-1) * sampling_period;

% Generate the message signal (modulating signal)
message_signal = 10*cos(2*pi*modulating_frequency*time);

% Generate the modulated and unmodulated carrier signals
modulated_carrier = exp(j * (2*pi*carrier_frequency*time + 2*pi*modulation_index*cumsum(message_signal)));
carrier = exp(j * 2*pi*carrier_frequency*time);

% Initialize necessary variables
phase_estimate = zeros(1, length(modulated_carrier));
error = zeros(1, length(modulated_carrier));
phase_detector_output = zeros(1, length(modulated_carrier));
vco_output = zeros(1, length(modulated_carrier));

phase_estimate(1) = 30; % Set initial phase estimate

% Start PLL loop
for n = 2:length(modulated_carrier)
    % Calculate VCO (Voltage Controlled Oscillator) output
    vco_output(n) = conj(exp(j * (2*pi*n*carrier_frequency/sampling_frequency + phase_estimate(n-1))));
    
    % Phase detector output
    phase_detector_output(n) = imag(modulated_carrier(n) * vco_output(n));
    
    % Loop Filter calculations
    proportional_control = proportional_gain * phase_detector_output(n);
    LPF_integration = integral_gain * (phase_detector_output(n) - phase_detector_output(n-1));
    
    % Update Phase error
    error(n) = error(n-1) + proportional_control + LPF_integration;
    
    % Update VCO: Update phase estimate
    phase_estimate(n) = phase_estimate(n-1) + error(n);
end

% Set time range for graph plotting
start_plot = 1;
end_plot = 1000;

% Start plotting
figure(1);

% Plot of unmodulated carrier
subplot(2,2,1);
plot(time(start_plot:end_plot), real(carrier(start_plot:end_plot)));
title('Unmodulated Carrier');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Plot of Message Signal
subplot(2,2,2);
plot(time(start_plot:end_plot), message_signal(start_plot:end_plot));
title('Message Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Plot of FM Signal
subplot(2,2,3);
plot(time(start_plot:end_plot), real(modulated_carrier(start_plot:end_plot)));
title('FM Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Plot of PLL Loop Filter Output
subplot(2,2,4);
plot(time(start_plot:end_plot), error(start_plot:end_plot));
title('PLL Loop Filter Output');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;
