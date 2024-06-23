% Carregar o dados_trainset do arquivo TRAIN
dados_train = readtable('Train.csv');

% Mapeamento dos valores para os atributos
atributo_smoking = containers.Map({'never smoked','formerly smoked','smokes','Unknown'},{0,1,2,3});
atributo_genero = containers.Map({'Male','Female'},{0,1});
atributo_residencia = containers.Map({'Rural','Urban'},{0,1});
atributo_casamento = containers.Map({'No','Yes'},{0,1});

% Converter valores para os atributos 'Smoking_status', 'Gender' e 'Residence_type' e 'ever_married'
dados_train.smoking_status = cellfun(@(x) atributo_smoking(x),dados_train.smoking_status);
dados_train.gender = cellfun(@(x) atributo_genero(x),dados_train.gender);
dados_train.Residence_type = cellfun(@(x) atributo_residencia(x),dados_train.Residence_type);
dados_train.ever_married = cellfun(@(x) atributo_casamento(x),dados_train.ever_married);


% Salvar o novo dados_trainset
writetable(dados_train, 'train_processado.csv'); 



