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

namespace ibex {
    DualAnnealing::DualAnnealing(const IntervalVector& box, const System& sys) : box(box), sys(sys) {}

    double DualAnnealing::f_obj(const IntervalVector& x, int ctr) const {
        std::cout << "ctr: " << ctr << std::endl;
        std::cout << "x: " << x << std::endl;
        return sys.f_ctrs[ctr].eval(x).mid();
    }

    Vector DualAnnealing::v1(const IntervalVector& box) {
        
        IntervalVector inicial(box.size());

        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); 
        int restriccion = std::round(restriccion1);

        for (int i = 0; i < box.size(); i++) {
            double random_num = RNG::rand(box[i].lb(), box[i].ub());
            inicial[i] = Interval(random_num, random_num);
        }
        
        double mejor = f_obj(inicial, restriccion);  

        double temperatura = 100.0;
        double alpha = 0.95;

        bool cambio = true;
        IntervalVector vecino = inicial;
        int iter = 0;
        while (cambio && iter < 50) {
            cambio = false;
            for (int i = 0; i < inicial.size(); i++) {
                double ruido = RNG::rand(0, 1);
                double magnitud = (box[i].ub() - box[i].lb()) * 0.1;
                ruido = ruido * magnitud;
                vecino[i] = Interval(inicial[i].lb() + ruido, inicial[i].ub() + ruido);
                
                double delta = f_obj(vecino, restriccion) - mejor;

                double randomReal = (double) rand() / (double) RAND_MAX; // Número aleatorio real entre [0,1]
                
                Interval expInterval = exp(-delta / temperatura);
                double expValue = expInterval.mid();  // Obtenemos el punto medio del intervalo.

                if (delta < 0 || randomReal < expValue) {
                    mejor = f_obj(vecino, restriccion);
                    inicial = vecino;
                    cambio = true;
                    break;
                } else {
                    vecino = inicial;
                }
            }
            // Geometrico
            temperatura = alpha * temperatura; 
            iter++;
        }

        return inicial.mid();
    }

}

