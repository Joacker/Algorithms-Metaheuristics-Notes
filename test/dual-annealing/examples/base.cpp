#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <tsallis_distribution.hpp>

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

        X_B = fun_per(X_B, lb, ub, dim, T, T2); // Llamada a fun_per con temperaturas

        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if(eval_X_B < eval_X_A || distribution(generator) < exp(-(eval_X_B - eval_X_A) / T)) {
            X_A = X_B;
        }

        T = alpha * T;
        T2 = alpha * T2; // Enfriamiento de la segunda temperatura
    }

    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';

    return 0;
}