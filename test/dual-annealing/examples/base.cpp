#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <random>

#include <tsallis_distribution.hpp>
#include "chain.hpp"
#include <pcg_random.hpp>

double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

std::vector<double> perturb(const std::vector<double>& X_B, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double T, double T2) {
    std::vector<double> X_B_new = X_B;
    std::random_device rd; // Obtener un número aleatorio de hardware
    std::mt19937 gen(rd()); // Sembrar el generador
    std::uniform_real_distribution<> dis(-1.0, 1.0); // Rango para el factor de perturbación

    for(int j = 0; j < dim; ++j) {
        double perturbation_factor = dis(gen);
        double delta = perturbation_factor * T + perturbation_factor * T2; // Combinación de ambas temperaturas
        X_B_new[j] += delta;
        // Asegurarse de que la nueva solución se mantenga dentro de los límites
        X_B_new[j] = std::min(std::max(X_B_new[j], lb[j]), ub[j]);
    }

    return X_B_new;
}

std::vector<double> local_search(const std::vector<double>& X, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double step_size, int max_local_iters, double (*f_obj)(const std::vector<double>&)) {
    std::vector<double> X_local = X;
    std::vector<double> grad(dim);

    for (int iter = 0; iter < max_local_iters; ++iter) {
        // Calcula el gradiente de f_obj en X_local
        // Esto es específico para tu función, asumiendo una función cuadrática simple aquí
        for (int j = 0; j < dim; ++j) {
            grad[j] = 2 * X_local[j]; // Derivada de x^2 es 2x
        }
        
        // Actualiza la solución en la dirección opuesta al gradiente
        for (int j = 0; j < dim; ++j) {
            X_local[j] -= step_size * grad[j];
            // Asegurarse de que la solución se mantenga dentro de los límites
            X_local[j] = std::min(std::max(X_local[j], lb[j]), ub[j]);
        }

        // Si el cambio es muy pequeño, terminar la búsqueda local
        if (std::inner_product(grad.begin(), grad.end(), grad.begin(), 0.0) < 1e-6) {
            break;
        }
    }

    return X_local;
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

double f_obj(const std::vector<double>& x);

int main() {
    int iter = 10000;
    std::vector<double> lb = {10, 0, 10, 0};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 100.0;
    double T2 = 50.0; // Segunda temperatura
    double alpha = 0.99;
    double step_size = 0.5; // Tamaño de paso para la búsqueda local
    int max_local_iters = 100; // Máximo número de iteraciones para la búsqueda local

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    std::vector<double> X_A(dim);
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }

    std::vector<double> X_opt = X_A; // Mejor solución encontrada
    double f_opt = f_obj(X_A); // Mejor valor de la función objetivo encontrada

    for(int i = 0; i < iter; ++i) {
        std::vector<double> X_B = perturb(X_A, lb, ub, dim, T, T2); // Perturba la solución actual

        X_B = local_search(X_B, lb, ub, dim, step_size, max_local_iters, f_obj); // Búsqueda local para refinar X_B

        double eval_X_B = f_obj(X_B);

        // Aceptación de la nueva solución basada en la función objetivo y la probabilidad de Metropolis
        if(eval_X_B < f_opt || distribution(generator) < exp(-(eval_X_B - f_opt) / T)) {
            X_A = X_B;
            if (eval_X_B < f_opt) {
                X_opt = X_B;
                f_opt = eval_X_B;
            }
        }

        // Actualiza las temperaturas
        T = alpha * T;
        T2 = alpha * T2; // Enfriamiento de la segunda temperatura
    }

    // Imprime la mejor solución encontrada
    std::cout << "Mejor solución: ";
    for(double xi : X_opt) std::cout << xi << ' ';
    std::cout << "\nMejor valor en la función objetivo: " << f_opt << '\n';
    return 0;
}