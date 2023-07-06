%EULER  Método de Euler para ED/PVI
%   yEuler = Euler(f,a,b,n,y0) Método numérico para a resolução de um PVI
%   y(i+1)=y(i)+h*f(t(i),y(i)),i=0,1....,n-1
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
%   yEuler(i+1) = y(i)+h*f(t(i),y(i)) , i =0,1,...,n-1
%
%   12/04/2023 - Martim Antunes(2022141890@isec.pt) 
%   12/04/2023 - Pedro Faneca (a2022134142@isec.pt)  

function yEuler= Euler(f,a,b,n,y0)

h = (b-a)/n;                % Tamanho de cada subintervalo (passo)
yEuler=zeros(1,n+1);        % Alocação de memória - vetor das ordenadas
t=a:h:b;                    % Alocação de memória - vetor das abcissas
yEuler(1) = y0;             % O primeiro valor de y é sempre y0 

    for i=1:n                   % O número de iterações vai ser igual a n
    
    yEuler(i+1)=yEuler(i)+h*f(t(i),yEuler(i)); % Aproximação do método de 
                                               %Euler para a iésima iteração
    
    end

end