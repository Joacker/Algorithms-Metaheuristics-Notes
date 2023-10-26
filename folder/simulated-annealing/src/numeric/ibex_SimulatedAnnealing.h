#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class SimulatedAnnealing{
        public:
            SimulatedAnnealing(const IntervalVector& box, const System& sys);
            double f_obj(const IntervalVector& x, int ctr) const;
            Vector fun_per(const Vector& X_B, const IntervalVector& box, int ctr);
            Vector v1(const IntervalVector& box);
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}