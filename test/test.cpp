#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

std::vector<double> fun_per(const std::vector<double>& X_B, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double T, double T2) {
    std::vector<double> X_B_new = X_B;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for(int j = 0; j < dim; ++j) {
        double delta = (distribution(generator) - 0.5) * (ub[j] - lb[j]);
        X_B_new[j] += delta * T2; // Perturbación influenciada por T2
        X_B_new[j] = std::min(std::max(X_B_new[j], lb[j]), ub[j]);
    }

    return X_B_new;
}

std::vector<double> local_search(const std::vector<double>& X, const std::vector<double>& lb, const std::vector<double>& ub, int dim) {
    std::vector<double> X_local = X;
    double best_eval = f_obj(X);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-0.1, 0.1);

    for (int i = 0; i < 100; ++i) { // 100 es el número de iteraciones de la búsqueda local
        std::vector<double> candidate = X_local;
        for (int j = 0; j < dim; ++j) {
            candidate[j] += distribution(generator);
            candidate[j] = std::min(std::max(candidate[j], lb[j]), ub[j]);
        }
        double candidate_eval = f_obj(candidate);
        if (candidate_eval < best_eval) {
            best_eval = candidate_eval;
            X_local = candidate;
        }
    }
    return X_local;
}

int main() {
    int iter = 10000;
    std::vector<double> lb = {10, -100, -100, -100};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1;
    double T2 = 10; // Temperatura de perturbación inicial más alta
    double alpha = 0.99;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    std::vector<double> X_A(dim);
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }

    for(int i = 0; i < iter; ++i) {
        std::vector<double> X_B = fun_per(X_A, lb, ub, dim, T, T2);

        X_B = local_search(X_B, lb, ub, dim); // Búsqueda local para refinar la solución

        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if(eval_X_B < eval_X_A || distribution(generator) < exp(-(eval_X_B - eval_X_A) / T)) {
            X_A = X_B;
        }

        T = alpha * T; // Enfriamiento de la temperatura de aceptación
        T2 = T2 / (1 + 0.01 * T2); // Enfriamiento más lento de la temperatura de perturbación
    }

    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';

    return 0;
}
