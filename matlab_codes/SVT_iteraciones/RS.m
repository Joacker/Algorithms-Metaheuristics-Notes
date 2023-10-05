clear all; clc;

% Parámetros que están involucrados en el método
iter = 1000;
lb = [-10, -10, -10, -10];
ub = [10, 10, 10, 10];
dim = length(lb);
F = @f_obj;
T = 1;
alpha = 0.99;

X_A = lb + (ub - lb).*rand(1, dim);
bestSolution = X_A;
bestEval = F(X_A);
bestSolutions = zeros(iter, dim);
% Vector para almacenar los mejores valores encontrados en cada iteración
bestEvals = zeros(1, iter);
for i = 1:iter
    % Introducir un factor de perturbación aleatorio para aumentar la variabilidad
    perturbation = rand(1, dim) * 2 - 1; % Vector aleatorio entre -1 y 1
    X_B = X_A + perturbation .* (ub - lb) * 0.1; % Añadir la perturbación, ajustar el 0.1 según sea necesario
    
    X_B = max(min(X_B, ub), lb); % Asegurarse de que X_B no esté fuera de los límites

    eval_X_A = F(X_A);
    eval_X_B = F(X_B);

    if eval_X_B < eval_X_A
        X_A = X_B;
    else
        r = rand();
        P = exp(-(eval_X_B - eval_X_A) / T);
        if r < P
            X_A = X_B;
        end
    end

    T = alpha * T;
    
    if eval_X_A < bestEval
        bestEval = eval_X_A;
        bestSolution = X_A;
    end
    bestEvals(i) = bestEval;
    bestSolutions(i, :) = bestSolution;
end

display("Mejor solución: " + mat2str(bestSolution))
display("Mejor evaluación: " + bestEval)
for i = 1:10:iter % Modificado para imprimir cada 10 iteraciones y evitar demasiada salida
    disp(['Iteración ', num2str(i), ': ', mat2str(bestSolutions(i, :)), ', Evaluación: ', num2str(F(bestSolutions(i, :)))]);
end

plot(1:iter, bestSolutions)
xlabel("Iteraciones")
ylabel("Mejores soluciones por componente")
legend("x1", "x2", "x3", "x4") % Ajusta según el número de dimensiones
figure;
plot(bestEvals);
xlabel('Iteraciones');
ylabel('Mejor valor de la función objetivo encontrado');
title('Evolución de la mejor solución');
grid on;