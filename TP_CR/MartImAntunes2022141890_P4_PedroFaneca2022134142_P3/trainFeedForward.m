function [precisaoGlobal, precisaoTeste, tempo] = trainFeedForward(neuroCamadas,FTreino,FAtivacao,divideF,trainRatio,valRatio,testRatio,savename)

if length(FAtivacao) ~= (length(neuroCamadas)+1)
    disp('O FAtivacao tem de ter o mesmo tamanho que o numero de camadas da rede + 1');
    return;
end


if((trainRatio + valRatio + testRatio) ~= 1) && ~isempty(divideF)
    disp("Ratios somados tem de dar 1");
    return;
end




if ~isfolder('./Redes')
    mkdir('./Redes')
end

if ~isfolder('./Redes/RedesTeste')
    mkdir('./Redes/RedesTeste')
end

if ~isfolder('./Redes/RedesGlobal')
    mkdir('./Redes/RedesGlobal')
end



data = readmatrix('Train_Completo.csv','Delimiter',',','DecimalSeparator','.');
in =data(:,2:end-1)';
t=data(:,end)';

tempoExecucao = tic;
precisaoGlobal = [];
precisaoTeste = [];
iteracoes = 50;

MelhorTeste = 0;
MelhorIndice = 0;
MelhorGlobal = 0;



for k = 1:iteracoes
    fprintf('Iteracao %d\n',k);

    net = feedforwardnet(neuroCamadas);   %CRIAR

    % COMPLETAR A RESTANTE CONFIGURACAO(FUNCAO TREINO,ATIVACAO,SEGMENTACAO)
    net.trainFcn=FTreino;


    if(~isempty(divideF))
        net.divideFcn = divideF;
        net.divideParam.trainRatio = trainRatio;
        net.divideParam.valRatio = valRatio;
        net.divideParam.testRatio = testRatio;
     else
        net.divideFcn = '';
    end

    net.trainParam.showWindow=0;

    
    for i = 1:length(neuroCamadas) + 1 
        net.layers{i}.transferFcn = FAtivacao{i};
    end

    [net,tr] = train(net, in, t);  %TREINAR
    
    %view(net);
    %disp(tr);
    
    out = sim(net, in);     %SIMULAR
    
    
    %VISUALIZAR DESEMPENHO
    %plotconfusion(t, out) % Matriz de confusao
    %plotperf(tr)         % Grafico com o desempenho da rede nos 3 conjuntos

    out  = (out >= 0.5);
    
    erro = perform(net,t,out);  %desempenho rede
    %fprintf('Erro na classificação dos 620 exemplos %f\n', erro)
    
    precisao=0;

    r = sum(out == t);

    precisao = r/size(out,2) *100;

    fprintf('Precisao total: %f\n', precisao);

    precisaoGlobal = [precisaoGlobal precisao]; %armazenar no vetor cada valor

    if(precisao > MelhorGlobal)
        MelhorGlobal = precisao;
        save(['./Redes/RedesGlobal/' savename '.mat'], 'net');
    end
   
   


    % SIMULAR A REDE APENAS NO CONJUNTO DE TESTE
    TInput = in(:, tr.testInd);
    TTargets = t(:, tr.testInd);
    
    out = sim(net, TInput);

    out  = (out >= 0.5);

   
    erro = perform(net, out,TTargets);
    %fprintf('Erro na classificação do conjunto de teste %f\n', erro)

     r = sum(out == TTargets);
    
    precisao = r/size(tr.testInd,2) *100;
    
    fprintf('Precisao teste: %f\n', precisao);
    precisaoTeste = [precisaoTeste precisao];
    
    if(precisao > MelhorTeste)
        MelhorTeste = precisao;
        save(['./Redes/RedesTeste/' savename '.mat'], 'net');
    end
    
end
    
precisaoGlobal = mean(precisaoGlobal);
precisaoTeste = mean(precisaoTeste);
fprintf('\nMédia Precisão Total: %f\n',precisaoGlobal);
fprintf('Média Precisão Teste: %f\n', precisaoTeste);

fprintf('\nMelhor precisao global: %f\n',MelhorGlobal);
fprintf('Melhor precisao teste: %f\n',MelhorTeste);
fprintf('Tempo de execução: %.2f segundos\n',toc(tempoExecucao));


end
