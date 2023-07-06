%RSimpson Calculo Integração Numérica através da Regra de Simpson
%   out_S = RSimpson(f,a,b,n)
%   out_S :=h/3(f(a)+s+f(b))
%
%INPUT:
%   f - função real de variável real x
%   [a, b] - extremos do intervalo da variável independente x
%   n - número de subintervalos ou iterações da regra
%OUTPUT: 
%   out_S - Resultado da área do Integral
%
%   25/05/2023 - Martim Antunes(2022141890@isec.pt)
%   25/05/2023 - Pedro Faneca (a2022134142@isec.pt)
function out_S = RSimpson(f,a,b,n)

h = (b-a)/n;                % Valor de cada subintervalo (passo)
x=a;                        % 'x' recebe o valor de 'a' (primeira abcissa)           
s = 0;                      % Inicializacao da variavel 's' a 0       
for i = 1:n-1
	x = x+h;                % Ao valor de 'x' e somado o passo ('h')
	if mod(i,2)==0          % Se i for par
		s = s+2*f(x);       % Ao valor de 's' e somado 2 vezes o valor da funcao
	else
		s = s+4*f(x);       % Ao valor de 's' e somado 2 vezes o valor da funcao
    end
end

out_S = h/3*((f(a)+s+f(b)));