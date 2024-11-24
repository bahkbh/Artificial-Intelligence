% 
% Simulation: Autocorrelation function of random binary wave
% 
clear all; 
close all; 


leng = 10; 
%leng = 30; 


% generation of a random sequence 
bin_seq = randb(leng); 

%modulation (BPS)
bin_signal = 2*bin_seq -1;  

% number of samples per second (for mimicing a continous signal) 
nSamples = 100; 

% random delay [0 1]; 
delay_t = round(rand(1,1)*nSamples); 

% signal 
y = kron(bin_signal,ones(1,nSamples)); 
y2 = circshift(y,[0 delay_t]); 
x = -5:1/nSamples:leng-5.00000001; 

% plot of a random binary wave and a shifted version  
plot(x,y,'b-'); hold; 
plot(x,y2,'r-');  
axis([-3 5 -2 2]); 
grid on; 

 
 n_iter = 10000; 
 cor_sum =0; 
 
 for ii=1:n_iter, 
	% generation of a random sequence 
	bin_seq = randb(leng); 
	%modulation 
	bin_signal = 2*bin_seq -1;  
	% random delay [0 1]; 
	delay = round(rand(1,1)*nSamples); 
	y = kron(bin_signal,ones(1,nSamples)); 	% discrete to continuous .. 
	y = circshift(y,[0,delay]); 
	cor_sum = cor_sum + y(5*nSamples)'* y(2*nSamples: (8*nSamples-1)); % correlation between a sample point and near points
end 

correlation = cor_sum / n_iter; % normalization 
x2 = -3:1/nSamples:(3-0.000001); 
figure(2); 
plot(x2,correlation); 
axis([-3 3 -0.5 1.3]); 
grid on; 




 
	
 
 