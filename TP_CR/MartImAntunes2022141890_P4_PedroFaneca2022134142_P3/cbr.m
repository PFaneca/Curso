function [] = cbr()

  similarity_threshold = 0.9;

  formatSpec = '%f%f%f%f%f%f%f%f%f%f%f';

  case_library = readtable('train_processado.csv', ...
        'Delimiter', ' , ', ...
        'Format', formatSpec);

    

  casosNaN = case_library(isnan(case_library{:,11}),:);   %tabela so com os NaN

  disp('Casos com NaN:');
  disp(casosNaN);
    
    
  case_library = case_library(~isnan(case_library{:,11}),:);   %Tabela toda sem os NaN


    for i=1:size(casosNaN,1)

        [retrieved_indexes, similarities,casosNaN(i,:)] = retrieve(case_library, casosNaN(i,:), similarity_threshold);


        if isempty(retrieved_indexes)
            while isempty(retrieved_indexes)
            similarity_threshold = similarity_threshold - 0.01;
            [retrieved_indexes, similarities,casosNaN(i,:)] = retrieve(case_library, casosNaN(i,:), similarity_threshold);
            end
        end

   
        retrieved_cases = case_library(retrieved_indexes, :);
        retrieved_cases.Similarity = similarities';

        casosNaN{i,11} = mode(retrieved_cases.stroke);  %Preenche o valor em falta com a moda dos valores de AVC (atributo "stroke") nos casos semelhantes recuperados.

        case_library = [case_library;casosNaN(i,:)];

    

    end


case_library= sortrows(case_library,1);

disp('Biblioteca filtrada: ');
disp(case_library);

writetable(case_library,'Train_Completo.csv','Delimiter',',');


end