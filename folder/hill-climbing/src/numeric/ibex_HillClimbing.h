#include <vector>
#include "ibex_IntervalVector.h"
#include "ibex_System.h"
#include <iostream> 
namespace ibex {
    class HillClimbing{
        public:
            HillClimbing(const IntervalVector& box, const System& sys);

            Vector v1(const IntervalVector& box);
            Vector v2(const IntervalVector& box);
            Vector v3(const IntervalVector& box);
            Vector v4(const IntervalVector& box);
        private:
            const IntervalVector& box;
            const System& sys;
            
    };
}