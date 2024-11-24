% Define the length of the noise signal
length = 10;

% Generate random noise
noise = rand(length, 1);
%noise = randn(length,1); 

% Plot the noise signal
plot(noise);

figure(2); 
hist(noise,100); 
%[f,xi] = ksdensity(noise);
%plot(xi,f);
grid on; 
