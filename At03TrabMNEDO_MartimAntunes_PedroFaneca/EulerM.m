%EULERM  Método de Euler Modificado para ED/PVI
%   yEulerM = EulerM(f,a,b,n,y0) Método numérico para a resolução de um PVI
%   k1 = f(t(i),y(i))
%   k2 = f(t(i+1), y(i) + k1*h)
%   y(i+1)=y(i)+h/2*(k1+k2)
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
%   y(i+1)=y(i)+h/2*(k1+k2)
%
%   12/04/2023 - Martim Antunes(2022141890@isec.pt) 
%   12/04/2023 - Pedro Faneca (a2022134142@isec.pt)  

function yEulerM=EulerM(f,a,b,n,y0)

h = (b-a)/n;                % Tamanho de cada subintervalo (passo)
yEulerM=zeros(1,n+1);       % Alocação de memória - vetor das ordenadas
t=a:h:b;                    % Alocação de memória - vetor das abcissas  
yEulerM(1) = y0;            % O primeiro valor de y é sempre y0

    for i=1:n                        % O número de iterações vai ser igual a n
        k1 = f(t(i),yEulerM(i));           % Inclinação no início do intervalo
        k2 = f(t(i+1), yEulerM(i) + k1*h); % Inclinação no fim do intervalo
        
        yEulerM(i+1)=yEulerM(i)+h/2*(k1+k2);  % Próximo valor aproximado da
                                              % solução do problema original
    
 
    end
 
end