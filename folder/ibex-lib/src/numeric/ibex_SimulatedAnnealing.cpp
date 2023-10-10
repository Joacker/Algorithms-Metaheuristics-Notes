#include "ibex_SimulatedAnnealing.h"
#include "ibex_IntervalVector.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include "ibex_Random.h"

namespace ibex {

SimulatedAnnealing::SimulatedAnnealing(const IntervalVector& box, const System& sys):box(box), sys(sys){

}

Vector SimulatedAnnealing::v1(const IntervalVector& box){
    IntervalVector current(box.size());
    double T = 1; // Temperatura inicial
    double alpha = 0.99; // Factor de enfriamiento

    // Escoger restriccion aleatoria
    int restriccion = std::round(RNG::rand(0, this->sys.nb_ctr - 1));

    // Solucion inicial
    for(int i=0; i < box.size(); i++){
        double random_num = RNG::rand(box[i].lb(), box[i].ub());
        current[i] = Interval(random_num, random_num);
    }

    Interval currentEval = this->sys.f_ctrs[restriccion].eval(current);
    IntervalVector neighbor;

    int iter = 0;
    while(T > 0.001 && iter < 10000) { // Condición de terminación basada en la temperatura y el número de iteraciones
        neighbor = current;

        // Generar vecino
        for(int i = 0; i < box.size(); i++) {
            double noise = RNG::rand(0, 1) * (box[i].ub() - box[i].lb()) * 0.1;
            neighbor[i] = Interval(current[i].lb() + noise, current[i].ub() + noise);
        }

        Interval neighborEval = this->sys.f_ctrs[restriccion].eval(neighbor);

        // Criterio de aceptación de Metropolis
        if(neighborEval.mid() < currentEval.mid() || 
           exp((currentEval.mid() - neighborEval.mid()) / T) > RNG::rand(0,1)) {
            current = neighbor;
            currentEval = neighborEval;
        }

        T *= alpha; // Enfriar la temperatura
        iter++;
    }

    return current.mid();
}

// Puedes adaptar las otras funciones (v2, v3, v4) de manera similar.
}