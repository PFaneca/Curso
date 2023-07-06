%RK2  Método de Runge-Kutta de 2ªordem para ED/PVI
%   yRK2 = RK2(f,a,b,n,y0) Método numérico para a resolução de um PVI
%   y(i+1)=y(i)+1/2*(k1+k2),i=0,1....,n-1
%   k1=h*f(t(i),y(i))
%   k2=h*f(t(i+1),y(i)+k1)
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
%   yRK2(i+1)=y(i)+1/2*(k1+k2),i=0,1....,n-1
%
%   13/04/2023 - Martim Antunes(2022141890@isec.pt) 
%   13/04/2023 - Pedro Faneca (a2022134142@isec.pt)  

function yRK2=RK2(f,a,b,n,y0)

h = (b-a)/n;                  % Tamanho de cada subintervalo (passo)
yRK2=zeros(1,n+1);            % Alocação de memória - vetor das ordenadas
t=a:h:b;                      % Alocação de memória - vetor das abcissas
yRK2(1) = y0;                 % O primeiro valor de y é sempre y0

    for i = 1:n                   % O número de iterações vai ser igual a n
    
    k1 = h*f(t(i), yRK2(i));            % Inclinação no início do intervalo
    k2 = h*f(t(i+1), yRK2(i) + k1);     % Inclinação no fim do intervalo
    
    yRK2(i+1) = yRK2(i) + 1/2*(k1 + k2);    % Próximo valor aproximado da 
                                            % solução do problema original
    
    end

end


