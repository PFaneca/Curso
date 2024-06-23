function startFile()

tempoExecucao = tic;
data = readmatrix('Start.csv','Delimiter',';','DecimalSeparator','.');

in =data(:,2:end-1)';
t=data(:,end)';
iteracoes=50;
precisaoTotal = [];
erroMedio = [];

for k=1:iteracoes
    fprintf('Iteracao %d\n',k);
 
    net=feedforwardnet(10);   %Criar rede

    %net.layers{1}.transferFcn = 'hardlims';
    %net.layers{2}.transferFcn = 'tansig';

   % net.trainFcn = 'trainbr';
    
    net.trainParam.showWindow=0;
 
    net.divideFcn = ''; % TODOS OS EXEMPLOS DE INPUT SAO USADOS NO TREINO
      
    net=train(net,in,t);  %Treina a rede
     
    out = sim(net, in);  %Simula rede /testa
    
    out  = (out >= 0.5);
     
    erro = perform(net,t,out);  %desempenho rede
        
     r = sum(out == t);

    precisao = r/size(out,2) *100;

    fprintf('Precisao total: %f\n', precisao);

    precisaoTotal = [precisaoTotal precisao];

    erroMedio = [erroMedio erro];

end

precisaoTotal = mean(precisaoTotal);
erroMedio = mean(erroMedio);
fprintf("\nMedia Precisão Total: %f\n",precisaoTotal);
fprintf("Erro: %f\n",erroMedio);
fprintf('Tempo de execução: %.2f segundos\n',toc(tempoExecucao));

end