%RK4SED Método de Runge-Kutta de ordem 4 para um Sistema de SED/PVI
%   [t,u,v] = RK4SED(f,g,a,b,n,u0,v0) Método numérico para a resolução de 
%   um SED (ordem 2)
%   u'= f(t,u,v), v'=g(t,u,v), t=[a, b], u(a)=u0 e v(a)=v0  
%
%INPUT:
%   f,g - funções das equações diferenciais
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   u0, v0 - condições iniciais t=a -> u=u0 e v=v0
%
%OUTPUT: 
%   [t,u,v] - vector das soluções aproximações e da discretização de t
%
%   06/05/2023 - Martim Antunes(2022141890@isec.pt) 
%   06/05/2023 - Pedro Faneca (a2022134142@isec.pt)

function [t,u,v] = RK4SED(f,g,a,b,n,u0,v0)

h = (b-a)/n;                          % Tamanho de cada subintervalo (passo)
t = a:h:b;                            % Alocação de memória
u = zeros(1,n+1);                     % Alocação de memória
v = zeros(1,n+1);                     % Alocação de memória
u(1) = u0;                            % O primeiro valor de u é sempre u0
v(1) = v0;                            % O primeiro valor de v é sempre v0
    for i = 1:n                       % O número de iterações vai ser igual a n
    
      k1u = h*f(t(i), u(i), v(i));    % Inclinação no início do intervalo
      k1v = h*g(t(i), u(i), v(i));    % Inclinação no início do intervalo

      k2u = h*f(t(i) + h/2, u(i) + k1u/2, v(i) + k1v/2);      % Inclinação no ponto 
                                                              % médio do intervalo
      k2v = h*g(t(i) + h/2, u(i) + k1u/2, v(i) + k1v/2);      % Inclinação no 
                                                              % ponto médio do intervalo

      k3u = h*f(t(i) + h/2, u(i) + k2u/2, v(i) + k2v/2);     % Inclinação (novamente) 
                                                             % no ponto médio do intervalo
      k3v = h*g(t(i) + h/2, u(i) + k2u/2, v(i) + k2v/2);     % Inclinação (novamente) 
                                                             % no ponto médio do intervalo
      k4u = h*f(t(i+1), u(i) + k3u, v(i) + k3v);             % Inclinação no final do intervalo
      k4v = h*g(t(i+1), u(i) + k3u, v(i) + k3v);             % Inclinação no final do intervalo

      u(i+1) = u(i)+1/6*(k1u+2*k2u+2*k3u+k4u);   % Aproximação do método 
                                                 % de RK4 para a iésima iteração

      v(i+1) = v(i)+1/6*(k1v+2*k2v+2*k3v+k4v);   % Aproximação do método 
                                                 % de RK4 para a iésima iteração
    end
end