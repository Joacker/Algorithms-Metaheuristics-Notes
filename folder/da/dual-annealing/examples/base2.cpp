#include </f2/app/dual-annealing/include/chain.hpp>
#include </f2/app/dual-annealing/third_party/pcg-cpp/include/pcg_random.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

// Define la función objetivo como en tu ejemplo de Simulated Annealing
struct ObjectiveFunction {
    // Función para evaluar la función objetivo
    double value(gsl::span<float const> x) const {
        double sum = 0.0;
        for (auto xi : x) {
            sum += xi * xi;
        }
        return sum;
    }

    // Función para manejar los límites de las variables (si es necesario)
    float wrap(float x) const {
        // Ejemplo: simplemente devuelve el mismo valor.
        // Modifica según sea necesario para tu problema específico.
        return x;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar la semilla del generador de números aleatorios

    // Parámetros de la función objetivo
    std::vector<float> lb = {-100, -100, -100, -100};
    std::vector<float> ub = {100, 100, 100, 100};

    // Configuración del algoritmo de Dual Annealing
    dual_annealing::param_t params = {/* q_V = */ 2.67, /* q_A = */ -5.0, /* t_0 = */ 10.0, /* num_iter = */ 1000, /* patience = */ 20};
    pcg32 generator{static_cast<uint64_t>(time(0))}; // Generador de números aleatorios
    ObjectiveFunction objective; // Función objetivo

    // Vector inicial de soluciones
    std::vector<float> x(lb.size());
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = lb[i] + (ub[i] - lb[i]) * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    // Ejecutar el algoritmo de Dual Annealing
    auto result = dual_annealing::minimize(objective, gsl::span<float>{x.data(), x.size()}, params, generator);

    // Imprimir el resultado
    std::cout << "Optimized solution: ";
    for (auto xi : x) {
        std::cout << xi << " ";
    }
    std::cout << "\nObjective value: " << result.func << std::endl;
    return 0;
}