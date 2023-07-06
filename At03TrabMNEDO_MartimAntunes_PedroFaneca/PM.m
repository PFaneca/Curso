%PM   Método Ponto Médio para ED/PVI
%   yPM = PM(f,a,b,n,y0) Método numérico para a resolução de um PVI
%   y(i+1) = y(i) + h*f(t(i) + h/2, y(i) + h*k1),,i=0,1....,n-1 
%   k1 = 0.5 * f(t(i), y(i));    
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
%   yPM(i+1) = yPM(i) + h*f(t(i) + h/2, yPM(i) + h*k1) ,i =0,1,...,n-1
%
%   22/04/2023 - Martim Antunes(2022141890@isec.pt) 
%   22/04/2023 - Pedro Faneca (a2022134142@isec.pt)  

function yPM = PM(f,a,b,n,y0)

h = (b-a)/n;                  % Tamanho de cada subintervalo (passo)
yPM=zeros(1,n+1);             % Alocação de memória - vetor das ordenadas
t=a:h:b;                      % Alocação de memória - vetor das abcissas
yPM(1) = y0;                  % O primeiro valor de y é sempre y0

    for i=1:n
     k1 = 0.5 * f(t(i), yPM(i));        % variável auxiliar
     yPM(i+1) = yPM(i) + h*f(t(i) + h/2, yPM(i) + h*k1);     
     % Próximo valor aproximado da solução do problema original
    
    end
end