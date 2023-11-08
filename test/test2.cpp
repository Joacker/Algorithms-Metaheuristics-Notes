#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

std::default_random_engine generator(std::random_device{}());
std::uniform_real_distribution<double> distribution(0.0, 1.0);
double q = 1.5; // Valor del parámetro de Tsallis

double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

bool tsallis_accept(double delta, double T, double q) {
    if (q == 1) {
        return exp(-delta / T) > distribution(generator);
    } else {
        double factor = (1 - (1-q) * delta / T);
        if (factor <= 0) return false;
        return pow(factor, 1 / (1-q)) > distribution(generator);
    }
}

std::vector<double> fun_per(const std::vector<double>& X_B, 
                            const std::vector<double>& lb,
                            const std::vector<double>& ub, int dim, double T, double T2) {
    std::vector<double> X_B_new = X_B;

    for(int j = 0; j < dim; ++j) {
        double delta = (distribution(generator) - 0.5) * (ub[j] - lb[j]);
        X_B_new[j] += delta * T2; // Perturbación influenciada por T2
        X_B_new[j] = std::min(std::max(X_B_new[j], lb[j]), ub[j]);
    }

    return X_B_new;
}

int main() {
    int iter = 10000;
    int iter_sin_mejora = 0;
    std::vector<double> lb = {0, -10, 10, 10};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1;
    double T2 = 0.1;
    double alpha_T = 0.99; // Factor de enfriamiento para T
    double alpha_T2 = 0.95; // Factor de enfriamiento para T2, si se desea distinto de alpha_T
    double tol_mejora = 1e-6; // Tolerancia de mejora relativa para el criterio de parada

    std::vector<double> X_A(dim);
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }
    double fval_mejor = f_obj(X_A);

    for(int i = 0; i < iter && iter_sin_mejora < 1000; ++i) {
        std::vector<double> X_B = fun_per(X_A, lb, ub, dim, T, T2);
        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);

        if(eval_X_B < eval_X_A || tsallis_accept(eval_X_B - eval_X_A, T, q)) {
            X_A = X_B;
            eval_X_A = eval_X_B;

            // Reinicia el contador si hay mejora
            if (eval_X_A < fval_mejor * (1 - tol_mejora)) {
                iter_sin_mejora = 0;
                fval_mejor = eval_X_A;
            }
        } else {
            // Incrementa el contador si no hay mejora
            ++iter_sin_mejora;
        }

        T *= alpha_T;
        T2 *= alpha_T2;
    }

    std::cout << "Solución: ";
    for(double xi : X_A) std::cout << xi << ' ';
    std::cout << "\nValor en la función objetivo: " << f_obj(X_A) << '\n';

    return 0;
}
