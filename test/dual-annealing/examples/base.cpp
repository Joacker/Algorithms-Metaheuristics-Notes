#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <numeric>

//#include <LBFGS.h>

using namespace LBFGSpp;

class FuncGrad {
public:
    FuncGrad(const std::vector<double>& lb, const std::vector<double>& ub, int dim)
        : m_lb(lb), m_ub(ub), m_dim(dim) {}

    double operator()(const Eigen::VectorXd& x, Eigen::VectorXd& grad) {
        double fx = 0;
        for (int i = 0; i < m_dim; ++i) {
            // Asume que f_obj es tu función objetivo
            fx += x[i] * x[i]; // f_obj(x[i]) para tu función específica
            grad[i] = 2 * x[i]; // Derivada de la función objetivo
        }
        return fx;
    }

private:
    std::vector<double> m_lb;
    std::vector<double> m_ub;
    int m_dim;
};

std::vector<double> local_search(const std::vector<double>& X, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double step_size, int max_local_iters) {
    // Inicializa el optimizador
    LBFGSParam<double> param;
    param.epsilon = 1e-6;
    param.max_iterations = max_local_iters;
    LBFGSSolver<double> solver(param);

    // Convierte el vector X a un vector de Eigen para L-BFGS
    Eigen::VectorXd x(dim);
    for (int i = 0; i < dim; ++i) {
        x[i] = X[i];
    }

    // Crea una instancia de la función y gradiente
    FuncGrad fg(lb, ub, dim);

    // Valor de la función objetivo después de la optimización
    double fx;
    int niter = solver.minimize(fg, x, fx);

    // Convierte el resultado de vuelta a std::vector
    std::vector<double> X_local(dim);
    for (int i = 0; i < dim; ++i) {
        X_local[i] = x[i];
    }

    return X_local;
}

double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for (double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

std::vector<double> fun_per(const std::vector<double>& X_B, const std::vector<double>& lb, const std::vector<double>& ub, int dim) {
    double mejor_eval = std::numeric_limits<double>::infinity();
    std::vector<double> mejor_sol, xq = X_B;
    
    int num_perturbaciones = rand() % dim + 1;  // Número aleatorio de elementos a perturbar

    for(int j = 0; j < num_perturbaciones; ++j) {
        int idx = rand() % dim; // Selecciona un índice aleatorio para perturbar

        // Aplica una perturbación variada
        double delta = (ub[idx] - lb[idx]) * ((double) rand() / RAND_MAX) * 0.1; // 10% del rango como máximo
        if(rand() % 2) {
            xq[idx] += delta; // Suma el delta
        } else {
            xq[idx] -= delta; // Resta el delta
        }

        // Asegurarse de que la solución perturbada esté dentro de los límites
        xq[idx] = std::max(lb[idx], std::min(xq[idx], ub[idx]));

        // Evalúa la nueva solución perturbada
        double eval_xq = f_obj(xq);
        if(eval_xq < mejor_eval) {
            mejor_eval = eval_xq;
            mejor_sol = xq;
        }
    }
    return mejor_sol;
}

int main() {
    int iter = 10000;
    std::vector<double> lb = {10, 0, 10, 0};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 10.0, T2 = 50.0, alpha = 0.99, step_size = 0.5;
    int max_local_iters = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    std::vector<double> X_A(dim), X_opt(dim);
    double f_opt = std::numeric_limits<double>::max();

    for (int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + distribution(gen) * (ub[i] - lb[i]);
    }

    for (int i = 0; i < iter; ++i) {
        std::vector<double> X_B = fun_per(X_A, lb, ub, dim, T, T2, gen);
        X_B = local_search(X_B, lb, ub, dim, step_size, max_local_iters);

        double eval_X_B = f_obj(X_B);
        if (eval_X_B < f_opt || distribution(gen) < exp(-(eval_X_B - f_opt) / T)) {
            X_A = X_B;
            if (eval_X_B < f_opt) {
                X_opt = X_B;
                f_opt = eval_X_B;
            }
        }

        T *= alpha;
        T2 *= alpha;
    }

    std::cout << "Mejor solución: ";
    for (double xi : X_opt) {
        std::cout << xi << ' ';
    }
    std::cout << "\nMejor valor en la función objetivo: " << f_opt << '\n';
    return 0;
}
