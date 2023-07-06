% ODE45 Método numérico para a resolução de um PVI=Funcão do Matlab
%   yODE45 = ODE45(f,a,b,n,y0) Método numérico para a resolução de um PVI
%INPUT:
%   f - função da equação diferencial, em t e y
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial
%
%OUTPUT: 
%   y - vetor das soluções aproximadas  
%
%   17/04/2023 - Martim Antunes(2022141890@isec.pt) 
%   17/04/2023 - Pedro Faneca  (a2022134142@isec.pt)

function yODE45=ODE45(f,a,b,n,y0)

h = (b-a)/n;                      % Tamanho de cada subintervalo (passo)
t=a:h:b;                          % Alocação de memória - vetor das abcissa
[~,yODE45] = ode45(f, t, y0);     % Aproximação através da função ODE45 e 
                                  % colocação dos valores no vetor y
yODE45 = yODE45';                 % Mudança da orientação do vetor

end