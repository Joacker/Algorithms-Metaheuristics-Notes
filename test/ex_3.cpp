#include "/test/dual-annealing/include/chain.hpp"

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

std::vector<double> local_search(std::vector<double>& X, const std::vector<double>& lb, const std::vector<double>& ub, int dim, double local_T) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, local_T);

    std::vector<double> X_local = X;
    double f_X = f_obj(X);

    for (int i = 0; i < dim; ++i) {
        double oldValue = X_local[i];
        double newValue = oldValue + distribution(generator);
        newValue = std::min(std::max(newValue, lb[i]), ub[i]); // Mantener dentro de los límites
        X_local[i] = newValue;

        double f_X_new = f_obj(X_local);
        if (f_X_new >= f_X) { // Si no hay mejora, revertir
            X_local[i] = oldValue;
        } else {
            f_X = f_X_new; // Actualizar el valor de la función
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

int main() {
    int iter = 1000;
    std::vector<double> lb = {0, 0, 0, 0};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1.0;
    double T2 = 0.1; // Segunda temperatura
    double alpha = 0.99;  // Factor de enfriamiento para T
    double beta = 0.81;   // Factor de calentamiento para T2

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int no_improvement_counter = 0;
    const int no_improvement_threshold = 100; // Establecer según el tamaño del problema y la naturaleza de la función objetivo

    std::vector<double> X_A(dim);
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }

    int iter_half = iter / 2;
    double best_eval = std::numeric_limits<double>::infinity();
    for(int i = 0; i < iter; ++i) {
        std::vector<double> X_B = X_A;

        X_B = fun_per(X_B, lb, ub, dim, T, T2); // Llamada a fun_per con temperaturas

        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if(eval_X_B < eval_X_A || distribution(generator) < exp(-(eval_X_B - eval_X_A) / T)) {
            X_A = X_B;
            eval_X_A = eval_X_B; // Asegúrate de actualizar el valor de la mejor solución encontrada
            no_improvement_counter = 0; // Reinicia el contador porque encontramos una mejor solución
        }else{
            no_improvement_counter++;
        }

        if (i < iter_half) {
            // En la primera mitad de las iteraciones, si estamos atascados, aumentar la temperatura local
            if (no_improvement_counter >= no_improvement_threshold) {
                T2 *= beta; // Aumenta la temperatura local para promover la exploración
                no_improvement_counter = 0; // Opcional: reinicia el contador
            }
        } else {
            // En la segunda mitad de las iteraciones, enfocarnos en la convergencia
            T2 *= alpha;
        }
        X_A = local_search(X_A, lb, ub, dim, T2);
        T *= alpha;
    }

    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';

    return 0;
}