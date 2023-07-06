%RTrapezios Calculo Integração Numérica através da Regra dos Trapézios
%   T = RTrapezios(f,a,b,n)
%   T = h/2(f(a)+2s+f(b))
%INPUT:
%   f - função real de variável real x
%   [a, b] - extremos do intervalo da variável independente x
%   n - número de subintervalos ou iterações da regra
%OUTPUT: 
%   T - Resultado da área do Integral
%
%   25/05/2023 - Martim Antunes(2022141890@isec.pt) 
%   25/05/2023 - Pedro Faneca (a2022134142@isec.pt)
function T = RTrapezios(f,a,b,n)

h = (b-a)/n;            % Valor de cada subintervalo (passo)
x = a;                  % 'x' recebe o valor de 'a' (primeira abcissa)
s = 0;                  % Inicializacao da variavel 's' a 0 

for i = 1:n-1
	x = x+h;            % Ao valor de 'x' e somado o passo ('h')
	s = s+f(x);         % Ao valor de 's' e somado 1 vez o valor da funcao
end

T = h/2*((f(a) +2*s + f(b)));