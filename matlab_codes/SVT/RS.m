clear all; clc;

% Parámetros que están involucrados en el método
% - Criterio de paro (n iteraciones)
iter = 10000
% Definición de cota superior y cota inferior (Variables de decisión)
lb = [-100, -100, -100, -100]
ub = [100, 100, 100, 100]
% Dimensiones
dim = length(lb)
% Llamamos a la suma de cuadrados
F = @f_obj
% - Temperatura
T = 1
% Coef alpha
alpha = 0.99

% Generar una primer Solución
% La solución debe de estar entre el limite superior y el límite inferior
% para cada una de las variables de decisión; se coloca el punto en la
% multiplicación al ser de tipo vectorial para que vaya de termino a
% termino
X_A = lb + (ub - lb).*rand(1,dim);

% Ciclo principal
for i = 1:iter
    %Crear una segunda solución
    X_B = X_A;
    % Realizamos perturbación sobre X_B
    X_B = fun_per(X_B, lb, ub, F, dim);

    % Evaluar las soluciones
    eval_X_A = F(X_A);
    eval_X_B = F(X_B);

    % Criterio de aceptación
    % Indica que X_A va a ser igual a X_B o la pimera solución va a ser
    % igual a la segunda solución, en el caso de que la segunda solución o
    % X_B sea mejor y de no ser así o en el caso de que X_A sea mejor que
    % X_B se va aplicar el criterio de Metropolis
    if eval_X_B < eval_X_A
        X_A = X_B;
    else
        % Entrega u número entre 0 y 1
        r = rand();
        P = exp( -(eval_X_B - eval_X_A) / T );
        % Si se cumple con el criterio de evaluación o probabilidad se va a
        % aceptar la peor solución y de no cumplirse o satisfacerse no se
        % va a acpetar la peor solución
        if r < P
            % Se va aceptar la peor solución o se podría decir que X_A es
            % igual a X_B, se está aceptando la peor solución, lo que
            % permite salir de óptimos locales
            X_A = X_B;
        end
    end
    % Ahora falta disminuir la temperatura, se amplifica por alpha siendo
    % simpre alpha menor que 1
    T = alpha*T;
end

% Imprimimos las soluciones
display("X_A: "+X_A)
display("eval_X_A: "+eval_X_A)

