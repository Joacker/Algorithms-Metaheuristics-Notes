function sol_per = fun_per(X_B, lb, ub, F, dim)
    mejor_eval = inf;
    mejor_sol = X_B;  % Inicializar con la solución actual para evitar problemas si no se encuentra una mejor
    
    for j = 1:dim
        xq = X_B;  % Reset xq en cada iteración
        d_lb = lb(j) - X_B(j);
        d_ub = ub(j) - X_B(j);
        xq(j) = xq(j) + d_lb + (d_ub - d_lb)*rand();  % Perturbar la dimensión j
        
        eval_xq = F(xq);
        
        if eval_xq < mejor_eval
            mejor_eval = eval_xq;
            mejor_sol = xq;
        end
    end
    
    sol_per = mejor_sol;
end