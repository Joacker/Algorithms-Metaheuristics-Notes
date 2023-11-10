#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <functional>

double f_obj(const std::vector<double>& x) {
    // Aplicar una función de suma de cuadrados
    double eval_fun = 0;
    for(double xi : x) {
        eval_fun += xi * xi;
    }
    return eval_fun;
}

std::vector<double> fun_per(const std::vector<double>& X_B, const std::vector<double>& lb, const std::vector<double>& ub, int dim) {
    double mejor_eval = std::numeric_limits<double>::infinity();
    std::vector<double> mejor_sol, xq = X_B;
    for(int j = 0; j < dim; ++j) {
        double d_lb = lb[j] - X_B[j];
        double d_ub = ub[j] - X_B[j];
        xq[j] = xq[j] + d_lb + (d_ub - d_lb) * ((double) rand() / RAND_MAX);
        double eval_xq = f_obj(xq);
        if(eval_xq < mejor_eval) {
            mejor_eval = eval_xq;
            mejor_sol = xq;
        }
    }
    return mejor_sol;
}

int main() {
    srand(time(0));  // Inicializar la semilla del generador de números aleatorios

    // Parámetros que están involucrados en el método
    int iter = 10000;
    std::vector<double> lb = {-100, -100, -100, -100};
    std::vector<double> ub = {100, 100, 100, 100};
    int dim = lb.size();
    double T = 1;
    double alpha = 0.99;

    // Generar una primer Solución
    std::vector<double> X_A(dim);
    for(int i = 0; i < dim; ++i) {
        X_A[i] = lb[i] + (ub[i] - lb[i]) * ((double) rand() / RAND_MAX);
    }

    std::vector<double> ruta(iter);

    // Ciclo principal
    for(int i = 0; i < iter; ++i) {
        // Crear una segunda solución
        std::vector<double> X_B = X_A;
        // Realizamos perturbación sobre X_B
        X_B = fun_per(X_B, lb, ub, dim);
        // Evaluar las soluciones
        double eval_X_A = f_obj(X_A);
        double eval_X_B = f_obj(X_B);
        // Criterio de aceptación
        if(eval_X_B < eval_X_A) {
            X_A = X_B;
        } else {
            double r = ((double) rand() / RAND_MAX);
            double P = exp( -(eval_X_B - eval_X_A) / T );
            if(r < P) {
                X_A = X_B;
            }
        }
        // Disminuir la temperatura
        T = alpha * T;
        ruta[i] = eval_X_A;
    }

    // Imprimimos las soluciones
    std::cout << "X_A: ";
    std::copy(X_A.begin(), X_A.end(), std::ostream_iterator<double>(std::cout, " "));
    std::cout << "\neval_X_A: " << f_obj(X_A) << std::endl;
    return 0;
}