%DFCentradas_3 Derivação Numérica - Fórmula das Diferenças Centradas (3 pontos)
% Formúla das Diferenças Centradas (3 pontos)
% f'(x(i))=(f(x(i+1))-f(x(i-1))/(2*h)
%
% INPUT:  f - função
%         [a, b] - intervalo de derivação
%         h - passo da discretização
%         y - imagens x vs y
% OUTPUT: [x, y] - malha de pontos
%         dydx - derivada de f
%
%   25/05/2023 - Martim Antunes(2022141890@isec.pt) 
%   25/05/2023 - Pedro Faneca (a2022134142@isec.pt)

function [x,y,dydx] = DFCentradas_3(f,a,b,h,y)

x = a:h:b;                     % Alocação de memória
n = length(x);                 % Número de pontos (tamanho do vetor de abcissas)

if nargin==4
    y=f(x);                    % y é a função f(x)
end

dydx = zeros(1,n);             % Alocação de memória

dydx(1) = (y(2)-y(1))/h;       % Derivada (aproximada) de f no ponto atual

for i = 2:n-1
    dydx(i) = (y(i+1)-y(i-1))/(2*h);       % Derivada (aproximada) de f no ponto atual
end

dydx(n)=(y(n)-y(n-1))/h;