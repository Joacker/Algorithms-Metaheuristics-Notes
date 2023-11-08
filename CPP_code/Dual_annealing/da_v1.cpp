#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <LBFGS.h>

using Eigen::VectorXd;
using LBFGSpp::LBFGSParam;
using LBFGSpp::LBFGSSolver;

// Calcula el gradiente de la función objetivo
void calculate_gradient(const std::vector<double>& x, std::vector<double>& grad) {
    for (size_t i = 0; i < x.size(); ++i) {
        grad[i] = 2.0 * x[i];
    }
}
double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

std::vector<double> fun_per(const std::vector<double>& X_B, 
                            const std::vector<double>& lb,
                            const std::vector<double>& ub, int dim, double T, double T2) {
    std::vector<double> X_B_new = X_B;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    for(int j = 0; j < dim; ++j) {
        double delta = (distribution(generator) - 0.5) * (ub[j] - lb[j]);
        X_B_new[j] += delta * T2 + delta * T; // Perturbación influenciada por ambas temperaturas
        X_B_new[j] = std::min(std::max(X_B_new[j], lb[j]), ub[j]);
    }
    
    return X_B_new;
}

std::vector<double> local_search(const std::vector<double>& x_initial,
                                const std::vector<double>& lb,
                                const std::vector<double>& ub) {
    // Convertir std::vector a Eigen::VectorXd para usar con LBFGSpp
    VectorXd x = Eigen::Map<const VectorXd>(x_initial.data(), x_initial.size());
    VectorXd g(x.size());

    // Parámetros para el algoritmo L-BFGS
    LBFGSParam<double> param;
    param.epsilon = 1e-6;
    param.max_iterations = 100;

    // Inicializa el solver
    LBFGSSolver<double> solver(param);
    
    // Definir la función lambda para la evaluación del objetivo y el gradiente
    auto fun = [&](const VectorXd& x, VectorXd& grad) {
        std::vector<double> x_std(x.data(), x.data() + x.size());
        std::vector<double> grad_std(grad.size());

        double f = f_obj(x_std);
        calculate_gradient(x_std, grad_std);

        // Asignar grad_std a grad
        Eigen::Map<VectorXd>(grad.data(), grad.size()) = 
            Eigen::Map<const VectorXd>(grad_std.data(), grad_std.size());

        return f;
    };

    // Ejecutar la optimización
    double fx;
    int niter = solver.minimize(fun, x, fx);

    // Convertir de nuevo a std::vector para mantener la interfaz consistente
    std::vector<double> x_optimized(x.data(), x.data() + x.size());
    return x_optimized;
}

int main() {
    int iter = 10000;
    std::vector<double> lb = {-100, -100, -100, -100};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1;
    double T2 = 0.1; // Segunda temperatura
    double alpha = 0.99;
    
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    std::vector<double> X_A(dim);
    
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }
    
    for(int i = 0; i < iter; ++i) {
        std::vector<double> X_B = X_A;

        // Recocido simulado: generación y aceptación de nuevas soluciones
        X_B = fun_per(X_B, lb, ub, dim, T, T2); // Llamada a fun_per con temperaturas
        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if(eval_X_B < eval_X_A || distribution(generator) < exp(-(eval_X_B - eval_X_A) / T)) {
            X_A = X_B;
            // Búsqueda local: aplicada inmediatamente después de aceptar una nueva solución
            X_A = local_search(X_A, lb, ub); // Búsqueda local para refinar la solución
        }

        // Enfriamiento de temperaturas
        T *= alpha;
        T2 *= alpha;
    }
    
    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';
    
    return 0;
}
