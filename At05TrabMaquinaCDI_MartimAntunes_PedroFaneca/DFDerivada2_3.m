%DFderivada2 Derivação Numérica -  Formúla da 2º Derivada (3 pontos)
% Formúla da 2º Derivada (3 pontos)
% f''(x(i))=(f(x(i+1))-f(x(i))/h
%
% INPUT:  f - função
%         [a, b] - intervalo de derivação
%         h - passo da discretização
%         y - imagens x vs y
% OUTPUT: [x, y] - malha de pontos
%         dydx - segunda derivada de f
%
%   25/05/2023 - Martim Antunes(2022141890@isec.pt) 
%   25/05/2023 - Pedro Faneca (a2022134142@isec.pt)
function [x,y,dydx] = DFDerivada2_3(f,a,b,h,y)

x=a:h:b;                    % Alocação de memória
n=length(x);                % Número de pontos (tamanho do vetor de abcissas)

if nargin==4
    y=f(x);                  % y é a função f(x)
end

dydx=zeros(1,n);             % Alocação de memória

dydx(1)=(y(3)-2*y(2)+y(1))/(h^2);

for i=2:n-1
    dydx(i)=(y(i+1)-2*y(i)+y(i-1))/(h^2);
end
dydx(n)=(y(n)-2*y(n-1)+y(n-2))/(h^2);
