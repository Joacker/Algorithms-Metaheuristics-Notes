#include </f2/app/dual-annealing/include/chain.hpp>
#include </f2/app/dual-annealing/third_party/pcg-cpp/include/pcg_random.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>

// Define la función objetivo como en tu ejemplo de Simulated Annealing
struct ObjectiveFunction {
    std::vector<double> valoresObjetivo;
    mutable size_t currentIndex = 0;
    float lb;  // Límite inferior para las variables
    float ub;  // Límite superior para las variables

    ObjectiveFunction(const std::string& csvFile) {
        std::ifstream file(csvFile);
        std::string line;
        getline(file, line); // Ignorar el encabezado

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string valor;
            for (int i = 0; i < 5; ++i) { // Saltar las primeras 5 columnas
                getline(ss, valor, ',');
            }
            double valorObjetivo;
            ss >> valorObjetivo;
            valoresObjetivo.push_back(valorObjetivo);
        }
    }

    double value(gsl::span<float const> x) const {
        if (currentIndex < valoresObjetivo.size()) {
            return valoresObjetivo[currentIndex++];
        }
        return 0.0; // Devuelve 0.0 si no hay más valores
    }
    float wrap(float x) const {
        // Ejemplo: simplemente devuelve el mismo valor.
        // Modifica según sea necesario para tu problema específico.
        return x;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Inicializar la semilla del generador de números aleatorios

    std::ifstream file("/f1/app/DualAnnealingData.csv");
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo CSV." << std::endl;
        return 1; // Retorna un código de error
    }

    std::string line;
    getline(file, line); // Ignorar el encabezado
    // Lee e imprime cada línea del archivo
    /*while (getline(file, line)) {
        std::cout << line << std::endl;
    }*/
    std::vector<float> lb_values;
    std::vector<float> ub_values;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string valor;
        double lb, ub;

        // Saltar las primeras dos columnas y leer LB y UB
        for (int i = 0; i < 2; ++i) {
            getline(ss, valor, ',');
        }

        ss >> lb;
        getline(ss, valor, ','); // Ignorar el valor después de LB
        ss >> ub;

        lb_values.push_back(lb);
        ub_values.push_back(ub);
    }

    file.close(); // Cierra el archivo

    // Imprimir los valores LB y UB
    /*std::cout << "Valores LB:" << std::endl;
    for (float lb : lb_values) {
        std::cout << lb << " ";
    }
    std::cout << "\nValores UB:" << std::endl;
    for (float ub : ub_values) {
        std::cout << ub << " ";
    }*/
    //std::cout << std::endl;

    dual_annealing::param_t params = {/* q_V = */ 2.67, /* q_A = */ -5.0, /* t_0 = */ 10.0, /* num_iter = */ 1000, /* patience = */ 20};
    pcg32 generator{static_cast<uint64_t>(time(0))}; // Generador de números aleatorios
    ObjectiveFunction objective("/f1/app/DualAnnealingData.csv"); // Función objetivo

    // Vector inicial de soluciones
    std::vector<float> x(lb_values.size());
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = lb_values[i] + (ub_values[i] - lb_values[i]) * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    // Ejecutar el algoritmo de Dual Annealing
    auto result = dual_annealing::minimize(objective, gsl::span<float>{x.data(), x.size()}, params, generator);
    std::cout << "Optimized solution: ";
    for (auto xi : x) {
        std::cout << xi << " ";
    }
    std::cout << "\nObjective value: " << result.func << std::endl;
    return 0;
}