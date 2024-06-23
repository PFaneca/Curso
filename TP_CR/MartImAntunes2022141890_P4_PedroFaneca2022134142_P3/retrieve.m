function [retrieved_indexes, similarities, new_case] = retrieve(case_library, new_case, threshold)

 weighting_factors = [1 2 3 4 1 2 4 3 4];

  max_values = get_max_values(case_library);



  retrieved_indexes = [];
    similarities = [];
%     lista={'gender','age','hypertension','heart_disease','ever_married ',' Residence_type','avg_glucose_level','bmi','smoking_status'};
%     for i=1:length(lista)
%         if ~isfield(new_case,lista{i})
%             weighting_factors(i)=0;
%         end
%     end

    for i=1:size(case_library,1)

        distances = zeros(1,9);

         if isfield(new_case,'gender')
        distances(1,1) = calculate_linear_distance(case_library{i,'gender'} / max_values('gender'), ... 
                                new_case.gender / max_values('gender'));
         end
    
         if isfield(new_case,'age')
        distances(1,2) = calculate_linear_distance(case_library{i,'age'} / max_values('age'), ... 
                                new_case.age / max_values('age'));
         end
    
         if isfield(new_case,'hypertension')
        distances(1,3) = calculate_linear_distance(case_library{i,'hypertension'} / max_values('hypertension'), ... 
                                new_case.hypertension / max_values('hypertension'));
         end
    
         
         if isfield(new_case,'heart_disease')
        distances(1,4) = calculate_linear_distance(case_library{i,'heart_disease'} / max_values('heart_disease'), ... 
                                new_case.heart_disease / max_values('heart_disease'));
         end
    
          if isfield(new_case,'ever_married')
        distances(1,5) = calculate_linear_distance(case_library{i,'ever_married'} / max_values('ever_married'), ... 
                                new_case.ever_married / max_values('ever_married'));
          end
    
          if isfield(new_case,'Residence_type')
        distances(1,6) = calculate_linear_distance(case_library{i,'Residence_type'} / max_values('Residence_type'), ... 
                                new_case.Residence_type / max_values('Residence_type'));
         end
    
          if isfield(new_case,'avg_glucose_level')
        distances(1,7) = calculate_linear_distance(case_library{i,'avg_glucose_level'} / max_values('avg_glucose_level'), ... 
                                new_case.avg_glucose_level / max_values('avg_glucose_level'));
          end
    
           if isfield(new_case,'bmi')
        distances(1,8) = calculate_linear_distance(case_library{i,'bmi'} / max_values('bmi'), ... 
                                new_case.bmi / max_values('bmi'));
           end
    
            if isfield(new_case,'smoking_status')
        distances(1,9) = calculate_linear_distance(case_library{i,'smoking_status'} / max_values('smoking_status'), ... 
                                new_case.smoking_status / max_values('smoking_status'));
           end
    
          



         DG =  (distances * weighting_factors') /sum(weighting_factors);  %multiplica e depois no final soma                    
         final_similarity = 1- DG;


         if final_similarity >= threshold
            retrieved_indexes = [retrieved_indexes i];
            similarities = [similarities final_similarity];
        end
        
        %fprintf('Case %d out of %d has a similarity of %.2f%%...\n', i, size(case_library,1), final_similarity*100);

    end

end



function [max_values] = get_max_values(case_library)

   key_set = {'gender', 'age', 'hypertension', 'heart_disease', 'ever_married', 'Residence_type', 'avg_glucose_level', 'bmi', 'smoking_status'};
value_set = {...
    max(case_library{:,'gender'}), ...
    max(case_library{:,'age'}), ...
    max(case_library{:,'hypertension'}), ...
    max(case_library{:,'heart_disease'}), ...
    max(case_library{:,'ever_married'}), ...
    max(case_library{:,'Residence_type'}), ...
    max(case_library{:,'avg_glucose_level'}), ...
    max(case_library{:,'bmi'}), ...
    max(case_library{:,'smoking_status'})
    };
    max_values = containers.Map(key_set, value_set);
end


function [res] = calculate_linear_distance(val1, val2)

    res = abs(val1 - val2);
end