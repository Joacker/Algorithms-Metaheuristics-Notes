#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <numeric>

#include <LBFGS.h>

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

std::vector<double> perturb(const std::vector<double>& X_B, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double T, double T2, std::mt19937& gen) {
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::vector<double> X_B_new = X_B;

    for (int j = 0; j < dim; ++j) {
        double perturbation_factor = dis(gen);
        double delta = perturbation_factor * (T + T2);
        X_B_new[j] = std::min(std::max(X_B_new[j] + delta, lb[j]), ub[j]);
    }

    return X_B_new;
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
        std::vector<double> X_B = perturb(X_A, lb, ub, dim, T, T2, gen);
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
