#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class DualAnnealing{
        public:
            DualAnnealing(const IntervalVector& box, const System& sys);
            double f_obj(const IntervalVector& x, int ctr) const;
            
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}