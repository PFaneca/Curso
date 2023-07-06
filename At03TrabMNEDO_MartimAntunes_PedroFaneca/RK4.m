%RK4  Método de Runge-Kutta de 4ªordem para ED/PVI
%   yRK4 = RK4(f,a,b,n,y0) Método numérico para a resolução de um PVI
%   y(i+1) = y(i) + 1/6*(k1 + 2*k2 + 2*k3 + k4), i=0,1....,n-1
%   k1 = h*f(t(i), y(i));
%   k2 = h*f(t(i)+h/2, y(i)+k1/2);
%   k3 = h*f(t(i)+h/2, y(i)+k2/2);
%   k4 = h*f(t(i)+h, y(i)+k3);
%   y'= f(t,y) com t=[a, b] e y(a)=y0 condição inicial  
%
%INPUT:
%   f - função da equação diferencial, em t e y
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial
%
%OUTPUT: 
%   y - vetor das soluções aproximadas
%   yRK4(i+1) = y(i) + 1/6*(k1 + 2*k2 + 2*k3 + k4), i=0,1....,n-1
%
%  17/04/2023 - Martim Antunes(2022141890@isec.pt) 
%  17/04/2023 - Pedro Faneca (a2022134142@isec.pt) 

function yRK4 = RK4(f,a,b,n,y0)

h = (b-a)/n;                   % Tamanho de cada subintervalo (passo)    
yRK4=zeros(1,n+1);             % Alocação de memória - vetor das ordenadas
t=a:h:b;                       % Alocação de memória - vetor das abcissas

yRK4(1) = y0;                  % O primeiro valor de y é sempre y0
    
    for i=1:n                  % O número de iterações vai ser igual a n
        
        k1 = h*f(t(i), yRK4(i));    % Inclinação no início do intervalo
        
        k2 = h*f(t(i)+h/2, yRK4(i)+k1/2);   % Inclinação no ponto médio do 
                                            % intervalo
        k3 = h*f(t(i)+h/2, yRK4(i)+k2/2);   % Inclinação (novamente) no 
                                            % ponto médio do intervalo
        k4 = h*f(t(i)+h, yRK4(i)+k3);       % Inclinação no final do intervalo
        
        yRK4(i+1) = yRK4(i) + 1/6*(k1 + 2*k2 + 2*k3 + k4);  
        % Próximo valor aproximado da solução do problema original
    end

end
