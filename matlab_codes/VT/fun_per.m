function sol_per = fun_per(X_B, lb, ub, F, dim)
    mejor_eval = inf
    for j = 1:dim
        xq = X_B
        % A partir de las siguientes variables se quiere generar números
        % aleatorios dentro de un espacio cerrado
        % Calcular la distancia que existe o el espacio que existe entre
        % lb(j) y la variable de solución X_B(j)
        d_lb = lb(j) - X_B(j)
        % se está calculando la distancia que existe entre el límite
        % superior para cada variable de decisión y la posición o el valor
        % actual de la solución X_B para cada variable de decisión
        d_ub = ub(j) - X_B(j)
        % Se hace específicamente para no obtener soluciones de más alla de
        % los límites de las variables de decisión (-100 hasta 100)
        xq(j) = xq(j) + d_lb + (d_ub - d_lb)*rand()
        % La evaluacion de la funcion objetivo en el vector perturbado
        eval_xq = F(xq)
        % Se comprará la evaluación (eval_xq) con la mejor_eval
        % para que a medida que ocurran las iteraciones guardar la mejor
        % solución y asignarla a la variable mejor_eval
        if eval_xq < mejor_eval
             mejor_eval = eval_xq
             % Guarda no la evaluacion de la funcion sino esa solucion que
             % al ser evaluada resulta ser mejor
             mejor_sol = xq
        end
    end
    sol_per = mejor_sol
end