% 모든 변수 초기화와 그래프 창 닫기
clear all; 
close all;

% 파라미터 설정
carrier_frequency = 1000;         % 캐리어 주파수 설정
sampling_frequency = 100000;      % 샘플링 주파수 설정
sample_count = 5000;              % 샘플 수 설정
modulating_frequency = 100;       % 변조 주파수 설정
modulation_index = 0.0628;        % 변조 지수 설정
proportional_gain = 0.15;         % 비례 상수 설정
integral_gain = 0.1;              % 적분 상수 설정

% 시간 벡터 생성
sampling_period = 1 / sampling_frequency; 
time = (0:sample_count-1) * sampling_period;

% 메시지 신호 생성
message_signal = cos(2*pi*modulating_frequency*time);

% 변조된 캐리어와 변조되지 않은 캐리어 생성
modulated_carrier = exp(j * (2*pi*carrier_frequency*time + 2*pi*modulation_index*cumsum(message_signal)));
carrier = exp(j * 2*pi*carrier_frequency*time);

% 필요한 변수들 초기화
phase_estimate = zeros(1, length(modulated_carrier));
error = zeros(1, length(modulated_carrier));
phase_detector_output = zeros(1, length(modulated_carrier));
vco_output = zeros(1, length(modulated_carrier));

phase_estimate(1) = 30; % 처음 위상 추정치 설정

% PLL 루프 시작
for n = 2:length(modulated_carrier)
    % VCO 계산
    vco_output(n) = conj(exp(j * (2*pi*n*carrier_frequency/sampling_frequency + phase_estimate(n-1))));
    
    % Phase detector
    phase_detector_output(n) = imag(modulated_carrier(n) * vco_output(n));
    
    % Loop Filter
    proportional_control = proportional_gain * phase_detector_output(n);
    LPF_integration = integral_gain * (phase_detector_output(n) - phase_detector_output(n-1));
    
    % Phase error 업데이트
    error(n) = error(n-1) + proportional_control + LPF_integration;
    
    % VCO 업데이트: 위상 추정치 업데이트
    phase_estimate(n) = phase_estimate(n-1) + error(n);
end

% 그래프를 그릴 시간 범위 설정
start_plot = 1;
end_plot = 1000;

% 그래프 그리기 시작
figure(1);

% 변조되지 않은 캐리어 그래프
subplot(2,2,1);
plot(time(start_plot:end_plot), real(carrier(start_plot:end_plot)));
title('변조되지 않은 캐리어');
xlabel('시간 (초)');
ylabel('진폭');
grid on;

% 100Hz 메시지 신호 그래프
subplot(2,2,2);
plot(time(start_plot:end_plot), message_signal(start_plot:end_plot));
title('메시지 신호');
xlabel('시간 (초)');
ylabel('진폭');
grid on;

% FM 그래프 (1KHz 캐리어가 100 Hz 메시지 신호로 변조됨)
subplot(2,2,3);
plot(time(start_plot:end_plot), real(modulated_carrier(start_plot:end_plot)));
title('FM 신호');
xlabel('시간 (초)');
ylabel('진폭');
grid on;

% PLL 루프 필터 출력 그래프
subplot(2,2,4);
plot(time(start_plot:end_plot), error(start_plot:end_plot));
title('PLL 루프 필터 출력');
xlabel('시간 (초)');
ylabel('진폭');
grid on;
