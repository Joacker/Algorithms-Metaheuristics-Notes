#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iterator>

// Función objetivo: suma de cuadrados
double f_obj(const std::vector<double>& x) {
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

// Función de perturbación
std::vector<double> perturb(const std::vector<double>& x, 
                            const std::vector<double>& lb,
                            const std::vector<double>& ub, 
                            std::default_random_engine& generator) {
    std::vector<double> x_new = x;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for(size_t i = 0; i < x.size(); ++i) {
        double delta = distribution(generator) - 0.5;
        x_new[i] += delta;
        x_new[i] = std::min(std::max(x_new[i], lb[i]), ub[i]);
    }

    return x_new;
}

int main() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int iter = 10000;
    std::vector<double> lb = {-100, -100, -100, -100};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1.0; // Temperatura inicial
    double alpha = 0.99; // Factor de enfriamiento

    std::vector<double> x_current(dim);
    for(int i = 0; i < dim; ++i) {
        x_current[i] = lb[i] + (ub[i] - lb[i]) * distribution(generator);
    }

    std::vector<double> x_best = x_current;
    double f_best = f_obj(x_best);

    for(int i = 0; i < iter; ++i) {
        std::vector<double> x_new = perturb(x_current, lb, ub, generator);
        double f_new = f_obj(x_new);

        if(f_new < f_best || distribution(generator) < exp(-(f_new - f_best) / T)) {
            x_current = x_new;
            f_best = f_new;
            x_best = x_new;
        }

        T *= alpha; // Enfriamiento de la temperatura
    }

    std::cout << "Mejor solución encontrada: ";
    for(double xi : x_best) {
        std::cout << xi << " ";
    }
    std::cout << "\nValor de la función objetivo: " << f_best << std::endl;

    return 0;
}
