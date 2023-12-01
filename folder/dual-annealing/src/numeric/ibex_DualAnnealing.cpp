#include "ibex_DualAnnealing.h"
#include "ibex_IntervalVector.h"
#include <vector>
#include <iomanip>
#include "ibex_Random.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>
#include <fstream> 

// Incluir las librerías para el algoritmo de Dual Annealing
//#include </app/src/numeric/dual-annealing/include/chain.hpp>
//#include </app/src/numeric/dual-annealing/third_party/pcg-cpp/include/pcg_random.hpp>

namespace ibex {

    DualAnnealing::DualAnnealing(const IntervalVector& box, const System& sys) : box(box), sys(sys) {}

    double DualAnnealing::f_obj(const IntervalVector& x, int ctr) const {
        return sys.f_ctrs[ctr].eval(x).mid();
    }

    Vector DualAnnealing::v1(const IntervalVector& box) {
        IntervalVector inicial(box.size());

        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); 
        int restriccion = std::round(restriccion1);

        /*std::ofstream csv_file("DualAnnealingData.csv", std::ios_base::app);  // Abrir en modo append

        for (int i = 0; i < box.size(); i++) {
            double lb = box[i].lb();
            double ub = box[i].ub();
            double random_num = RNG::rand(box[i].lb(), box[i].ub());
            inicial[i] = Interval(random_num, random_num);

            double mejor = f_obj(inicial, restriccion); // Llamada a f_obj
            csv_file << box.size() << "," << restriccion << "," << lb << "," << ub << "," << random_num << "," << mejor << "\n";
        }*/
        //csv_file.close();
        // Configuración del algoritmo de Dual Annealing
        //dual_annealing::param_t params = {/* q_V = */ 2.67, /* q_A = */ -5.0, /* t_0 = */ 10.0, /* num_iter = */ 1000, /* patience = */ 20};
        //pcg32 generator{static_cast<uint64_t>(time(0))}; // Generador de números aleatorios

        // Ejecutar el algoritmo de Dual Annealing
        /*auto result = dual_annealing::minimize([this, restriccion](const std::vector<float>& x) {
            IntervalVector iv(x.size());
            for (size_t i = 0; i < x.size(); ++i) {
                iv[i] = Interval(x[i]);
            }
            return f_obj(iv, restriccion);
        }, gsl::span<float>{inicial.mid().data(), inicial.mid().size()}, params, generator);*/

        // Procesar y devolver el resultado
        /*IntervalVector resultadoOptimizado(result.x.size());
        for (size_t i = 0; i < result.x.size(); ++i) {
            resultadoOptimizado[i] = Interval(result.x[i]);
        }*/
        return inicial.mid();
    }
    Vector DualAnnealing::v2(const IntervalVector& box) {
        IntervalVector inicial(box.size());

        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); 
        int restriccion = std::round(restriccion1);

        std::ifstream csv_file("ResultDualAnnealingData.csv");  // Abrir en modo append

        
        return inicial.mid();
    }
}