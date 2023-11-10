#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include "tsallis_distribution.hpp"


double f_obj(const std::vector<double>& x) {
    double sum = 0.0;
    for (double xi : x) {
        sum += xi * xi;
    }
    return sum;
}

// Actualiza la función para usar la distribución de Tsallis para la perturbación
std::vector<double> perturb_tsallis(std::vector<double>& X, 
                                    tsallis_distribution_t& tsallis_dist, 
                                    std::default_random_engine& generator) {
    std::vector<double> X_new(X.size());
    for (size_t j = 0; j < X.size(); ++j) {
        X_new[j] = X[j] + tsallis_dist(generator);  // Genera un nuevo punto
    }
    return X_new;
}

// Implementa la función de aceptación de Tsallis
bool tsallis_accept(double delta, double T, double q, std::default_random_engine& generator) {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    if (q == 1.0) {
        return exp(-delta / T) > distribution(generator);
    } else {
        double factor = (1 - (1 - q) * delta / T);
        if (factor <= 0) return false;
        return pow(factor, 1 / (1 - q)) > distribution(generator);
    }
}

int main() {
    std::default_random_engine generator(std::random_device{}());
    double q = 1.5; // Parámetro de la distribución de Tsallis
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    tsallis_distribution_t tsallis_dist(q, 1.0); // Inicializa la distribución con q y una temperatura inicial

    int iter = 10000;
    std::vector<double> lb = {-100, -100, -100, -100};
    std::vector<double> ub = {100, 100, 100, 100};
    double T = 1; // Temperatura de aceptación inicial
    double alpha = 0.99; // Factor de enfriamiento para T

    std::vector<double> X_A(lb.size());
    for(size_t i = 0; i < X_A.size(); ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }

    double fval_mejor = f_obj(X_A);

    for(int i = 0; i < iter; ++i) {
        std::vector<double> X_B = perturb_tsallis(X_A, tsallis_dist, generator);
        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if (tsallis_accept(eval_X_A - eval_X_B, T, q, generator)) {
            X_A = X_B;
            fval_mejor = eval_X_B;
        }

        T *= alpha; // Enfriamiento de la temperatura de aceptación
    }
    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';

    return 0;
}