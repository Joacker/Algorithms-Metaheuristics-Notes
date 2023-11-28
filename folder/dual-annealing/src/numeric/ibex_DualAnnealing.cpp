#include "ibex_DualAnnealing.h"
#include "ibex_IntervalVector.h"
#include <vector>
#include <iomanip>
#include "ibex_Random.h"
#include <iostream>
#include </app/src/numeric/dual-annealing/third_party/pcg-cpp/include/pcg_random.hpp>
#include </app/src/numeric/dual-annealing/include/chain.hpp>  

namespace ibex {
    DualAnnealing::DualAnnealing(const IntervalVector& box, const System& sys) : box(box), sys(sys) {
        srand(static_cast<unsigned int>(time(0)));  // Inicializar la semilla del generador de números aleatorios
    }

    double DualAnnealing::f_obj(const IntervalVector& x, int ctr) const {
        return sys.f_ctrs[ctr].eval(x).mid();
    }

    Vector DualAnnealing::v1(const IntervalVector& box) {
        // Configuración del algoritmo de Dual Annealing
        dual_annealing::param_t params = {/* q_V = */ 2.67, /* q_A = */ -5.0, /* t_0 = */ 10.0, /* num_iter = */ 1000, /* patience = */ 20};
        pcg32 generator(static_cast<uint64_t>(time(0)));  // Generador de números aleatorios

        // Adaptar la función objetivo para trabajar con Ibex
        auto adaptedObjective = [&](const std::vector<float>& x) -> double {
            IntervalVector ibexVector(x.size());
            for (size_t i = 0; i < x.size(); ++i) {
                ibexVector[i] = Interval(x[i]);
            }
            return this->f_obj(ibexVector, /* ctr index */);  // Asigna el índice ctr adecuado
        };

        // Convertir IntervalVector a un vector de float para usar con minimize
        std::vector<float> x(box.size());
        for (size_t i = 0; i < x.size(); ++i) {
            x[i] = static_cast<float>(box[i].mid());  // Usamos el punto medio del intervalo
        }

        // Ejecutar el algoritmo de Dual Annealing
        auto result = dual_annealing::minimize(adaptedObjective, gsl::span<float>{x.data(), x.size()}, params, generator);

        // Convertir el resultado de vuelta a IntervalVector
        IntervalVector resultVector(box.size());
        for (size_t i = 0; i < x.size(); ++i) {
            resultVector[i] = Interval(x[i]);
        }

        // Retorna el vector resultante adaptado a IntervalVector
        return resultVector;
    }

}

