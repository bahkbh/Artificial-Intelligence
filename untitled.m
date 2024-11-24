clear
 
delta_f=input('Δf를 입력세요.(Hz) : ');
loop_freq=input('loop의 natural frequecy를 입력하세요.(Hz) : ' );
damping_factor=input('loop damping factor를 입력하세요.(보통은 0.707을 씀)(damping_factor) : ');
 
number_of_points=input('시뮬레이션하려는 지점의 개수를 입력하세요. : ');
sampling_freq=input('sampling frequencyf를 입력하세요. : ');
 
t=(0:(number_of_points-1))/sampling_freq; %시간을 정의하였다
T=1/sampling_freq;   %T는 시뮬레이션 계단 크기를 나타낸다. 이 값은 sampling frequency의 역수이다
setting_time=fix(number_of_points/25); %settling time을 정의하였다 fix란 0 방향으로 반올림 하는 함수이다. 시뮬레이션 지점 개수의 1/25배, 즉 4%로 설정된 settling time은 아래 주석에서 언급하는 과도현상을 방지할수 있는 역할을 한다.
 
Kt=4*pi*damping_factor*loop_freq; %2-order PLL에서 gain을 정의하였다. overall gain으로서 4*π*감쇠인자*natural frequecy의 값이다.
a=pi*loop_freq/damping_factor; %2-order PLL에서 루프필터를 정의할때 라플라스로 표현을 1+a/S로 표현을 하였다. 여기서 parameter인 a를 다음과 같이 나타낸다.
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%아래의 5개의 0 값은 먼저 초기화를 시켜주기 위해 값을 모두 0으로 지정하였다.		  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
filter_input_last=0;
filter_output_last=0;
vco_input_last=0;
vco_output_last=0;
vco_output=0; 
n=1;
while(n<=number_of_points) %입력한 number_of_points의 개수만큼 반복실행을 위해 for문을 이용하였다
    if n< setting_time %settling time 보다 작을 경우
        freq_input(n)=0; 
        phase_of_input=0;
    else
        freq_input(n)=delta_f;
        phase_of_input=2*pi*delta_f*T*(n-setting_time);
    end
    %Phase detector%
    Q1=phase_of_input-vco_output; %위상의 차이를 구한다
    Q2=sin(Q1); %위상의 차이를 구한후에 sin()의 함수에 집어 넣는다.
    Q3=Kt*Q2; %검출기를 통과한 값에 2-order PLL의 gain인 Kt를 곱한다.
    filter_input=a*Q3; %s3값과 loop filter의 parameter인 a를 곱하였다.
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%아래는 trapezoidal approximation이라는 방법으로서 적분의 계산을 아주 평범한 사칙연산으로   % %근사화를 시킬수 있는 공식이다. 총 2번의 trapezoidal approximation이 쓰였는데 그 이유는     %
%하나는 loof filter의 라플라스 식이 1+a/S 즉 time domain으로 보면 integral인 형태이므로     % %trapezoidal approximation를 이용하였다. 다른 하나는 VCO에서 integral의 계산이 포함돼      %
%있으므로 trapezoidaㅣ %approximation을 이용하였다. 단 주의해야할 점은 이전값들(n-1에서의  % %함수값들)은 반드시 초기화를 시켜주어야 한다. 적분기의 입력을 초기화를 하면 일반적으로 과도   % %응답이 발생하여 찌그러진 파형이 관측된다.                                                  % %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   

    %loop filter%
    %%%%첫번째 trapezoidal approximation.
    filter_output=filter_output_last+(T/2)*(filter_input+filter_input_last);  %loop filter가 second-order이기 때문에 이용하였다.
    filter_input_last=filter_input; %주어진 trapezoidal approximation의 공식에 넣기 위한 변수 선언이다. 위에서 언급하였듯이 반드시 초기화를 한 뒤에 루프에 넣어야 하므로 다음 for문을 위해 다음과 같이 선언한다.
    filter_output_last=filter_output; %주어진 trapezoidal approximation의 공식에 넣기 위한 변수 선언이다. 위에서 언급하였듯이 반드시 초기화를 한 뒤에 루프에 넣어야 하므로 다음 for문을 위해 다음과 같이 선언한다.
    vco_input=Q3+filter_output; %주어진 trapezoidal approximation의 공식에 넣기 위한 변수 선언이다. 위에서 언급하였듯이 반드시 초기화를 한 뒤에 루프에 넣어야 하므로 다음 for문을 위해 다음과 같이 선언한다.
   
    %vco%
    %%%%두번째 trapezoidal approximation.
    vco_output=vco_output_last+(T/2)*(vco_input+vco_input_last); %vco를 구할떄 적분기호가 있으므로 이용하였다.
    vco_input_last=vco_input; %주어진 trapezoidal approximation의 공식에 넣기 위한 변수 선언이다. 위에서 언급하였듯이 반드시 초기화를 한 뒤에 루프에 넣어야 하므로 다음 for문을 위해 다음과 같이 선언한다.
    vco_output_last=vco_output; %주어진 trapezoidal approximation의 공식에 넣기 위한 변수 선언이다. 위에서 언급하였듯이 반드시 초기화를 한 뒤에 루프에 넣어야 하므로 다음 for문을 위해 다음과 같이 선언한다.
    freq_output_of_vco(n)=vco_input/(2*pi);
    
    
    freq_error(n)=freq_input(n)-freq_output_of_vco(n);
    phase_error(n)=Q1;
    n=n+1;
end
 
figure(1) %입력해주는 step모양에 따라 주파수의 차이가 점차 줄어 들면서 결국엔 rock이 되어 같이 움직임을 볼 수 있는 그래프이다.
plot(t,freq_input,t,freq_output_of_vco); xlabel('time(s)'), ylabel('frequency(Hz)'), grid;
 
figure(2) %두번째 그림에서는 위상의 차이가 점차 2π의 정수배에 근접하는 것을 보여주는 그래프이다.
plot(t,phase_error/2/pi); xlabel('time(s)'), ylabel('phase error / 2π'), grid;
 
figure(3) %세번째 그림에서는 주파수의 차이가 점차 0에 근접하는 것을 보여주는 그래프이다.
plot(t,freq_error); xlabel('time(s)'), ylabel('frequency error(Hz)'), grid;