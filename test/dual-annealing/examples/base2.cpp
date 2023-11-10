#include "chain.hpp"  // Asume que esto incluye la implementación de Dual Annealing
#include <pcg_random.hpp>  // Generador de números aleatorios
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <gsl/gsl-lite.hpp> // Asegúrate de incluir la librería GSL

// Función objetivo del segundo código
float f_obj(const std::vector<float>& x) {
    float eval_fun = 0.0f;
    for(float xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

int main() {
    srand(0); // Inicializar la semilla del generador de números aleatorios con el tiempo actual

    std::vector<float> lb = {-100.0f, -100.0f, -100.0f, -100.0f}; // Límites inferiores
    std::vector<float> ub = {100.0f, 100.0f, 100.0f, 100.0f};    // Límites superiores
    size_t dim = lb.size(); // Dimensión del problema de optimización

    // Inicialización del generador de números aleatorios para Dual Annealing
    pcg32 generator{1230045}; // Generador de números aleatorios

    auto energy_fn = [](gsl::span<const float> x) -> float {
        return f_obj(std::vector<float>(x.begin(), x.end()));
    };

    auto local_search_parameters = tcm::lbfgs::lbfgs_param_t{};
    local_search_parameters.x_tol = 1e-5f;

    // Configuración de los parámetros de Dual Annealing
    auto const params = dual_annealing::param_t{
                                            /*q_V=*/2.62f, 
                                            /*q_A=*/-5.0f, 
                                            /*t_0=*/5230.0f, 
                                            /*num_iter=*/10000, 
                                            /*patience=*/100};

    // Punto de inicio para Dual Annealing
    std::vector<float> xs(dim);
    for(size_t i = 0; i < dim; ++i) {
        xs[i] = lb[i] + (ub[i] - lb[i]) * static_cast<float>(rand()) / RAND_MAX;
    }

    // Ejecutar el algoritmo de Dual Annealing
    auto const result = dual_annealing::minimize(
        energy_fn, gsl::make_span(xs), params, local_search_parameters, generator);

    // Imprimir los resultados
    std::cout << "Best solution found:\n";
    for(auto xi : result.x) { // Asumiendo que result.x es la mejor solución encontrada
        std::cout << xi << ' ';
    }
    std::cout << "\nFunction value: " << result.func << "\n";
    std::cout << "Number of iterations: " << result.num_iter << "\n";
    std::cout << "Number of function evaluations: " << result.num_f_evals << "\n";
    std::cout << "Acceptance: " << result.acceptance << std::endl;

    return 0;
}
