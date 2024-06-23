function testFile()

data = readmatrix('Test.csv','Delimiter',';','DecimalSeparator','.');
in =data(:,2:end-1)';
t=data(:,end)';
tempoExecucao = tic;

%Rede com melhor desempenho- rede17
rede1 = load('Redes\RedesGlobal\rede17.mat'); 
rede2 = load('Redes\RedesGlobal\rede3.mat');
rede3 = load('Redes\RedesGlobal\rede13.mat');
    
% Extrair as redes dos arquivos carregados
net = rede3.net;


% Simular a rede global nos dados de teste
out = sim(net, in);

out = (out >= 0.5);

erro = perform(net,t,out);  %desempenho rede

precisaoTotal = 0;

%Calcular precisao Total
r = sum(out == t);
precisaoTotal = r/size(out,2) *100;
    
fprintf('\nPrecisão Total: %f\n',precisaoTotal);
fprintf('Erro: %f\n',erro);
fprintf('Tempo de execução: %.2f segundos\n',toc(tempoExecucao));

end