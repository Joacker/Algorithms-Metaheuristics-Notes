#include "ibex_HillClimbing.h"
#include "ibex_IntervalVector.h"
#include <vector>
#include <iomanip>
#include "ibex_Random.h"
namespace ibex {
    HillClimbing::HillClimbing(const IntervalVector& box, const System& sys):box(box), sys(sys){


    }
    Vector HillClimbing::v1(const IntervalVector& box){
        IntervalVector inicial(box.size());
        int sizee=box.size();
        double restriccion1=RNG::rand(0,this->sys.nb_ctr-1); // Escoger restriccion aleatoria
        int restriccion=std::round(restriccion1);
        //------------Solucion inicial-----------------
        for(int i=0;i<box.size();i++){
            double random_num = RNG::rand(box[i].lb(),box[i].ub());
            inicial[i]=Interval(random_num,random_num);
        }
        
        //----------------------------------------------
        Interval mejor=this->sys.f_ctrs[restriccion].eval(inicial);  // Evaluar la restriccion en la solucion inicial
        bool cambio=true;
        //------------Generar vecindario----------------
        IntervalVector vecino=inicial;
        int iter=0;
        while( cambio && iter<50 ){
            cambio=false;
            for(int i=0;i<inicial.size();i++){
            //--------------Operador de movimiento----------------
            double ruido= RNG::rand(0,1);
            double magnitud= (box[i].ub()-box[i].lb())*0.1;
            ruido=ruido*magnitud;
            vecino[i]=Interval(inicial[i].lb()+ruido,inicial[i].ub()+ruido);
            //--------------funcion de evaluacion----------------
            if(fabs(this->sys.f_ctrs[restriccion].eval(vecino).mid())<fabs(mejor.mid())){
            //----------------------------------------------
                mejor=this->sys.f_ctrs[restriccion].eval(vecino);
                inicial=vecino;
                cambio=true;
                break;
            }else{
                vecino=inicial;
            }
        }
            
            iter++;
        }
            

        //----------------------------------------------
        return inicial.mid();
    }

        Vector HillClimbing::v2(const IntervalVector& box){
        IntervalVector inicial(box.size());
        int sizee=box.size();
        IntervalVector mejor_vecino(box.size());
        double restriccion1=RNG::rand(0,this->sys.nb_ctr-1); // Escoger restriccion aleatoria
        int restriccion=std::round(restriccion1);
        //------------Solucion inicial-----------------
        for(int i=0;i<box.size();i++){
            double random_num = RNG::rand(box[i].lb(),box[i].ub());
            inicial[i]=Interval(random_num,random_num);
        }
        //----------------------------------------------
        Interval mejor=this->sys.f_ctrs[restriccion].eval(inicial);  // Evaluar la restriccion en la solucion inicial
        bool cambio=true;
        //------------Generar vecindario----------------
        IntervalVector vecino=inicial;
        int iter=0;
        while( cambio && iter<50 ){
            cambio=false;
            for(int i=0;i<inicial.size();i++){
            //--------------Operador de movimiento----------------
            double ruido= RNG::rand(0,1);
            double magnitud= (box[i].ub()-box[i].lb())*0.1;
            ruido=ruido*magnitud;
            vecino[i]=Interval(inicial[i].lb()+ruido,inicial[i].ub()+ruido);
            //--------------funcion de evaluacion----------------
            if(fabs(this->sys.f_ctrs[restriccion].eval(vecino).mid())<fabs(mejor.mid())){
            //----------------------------------------------
                mejor=this->sys.f_ctrs[restriccion].eval(vecino);
                mejor_vecino=vecino;
                vecino=inicial;
                cambio=true;
            }else{
                vecino=inicial;
            }
        }
            inicial=mejor_vecino;

            iter++;
        }
        //----------------------------------------------
        return inicial.mid();
    }
        Vector HillClimbing::v3(const IntervalVector& box){
        IntervalVector inicial(box.size());
        double suma=0;
        double mejor=0;
        int sizee=box.size();
        double restriccion1=RNG::rand(0,this->sys.nb_ctr-1); // Escoger restriccion aleatoria
        int restriccion=std::round(restriccion1);
        //------------Solucion inicial-----------------
        for(int i=0;i<box.size();i++){
            double random_num = RNG::rand(box[i].lb(),box[i].ub());
            inicial[i]=Interval(random_num,random_num);
        }
        //----------------------------------------------
        // Evaluar la restriccion en la solucion inicial
        for (int i=0;i<sys.nb_ctr;i++){
                mejor+=fabs(this->sys.f_ctrs[i].eval(inicial).mid());
            }
        bool cambio=true;
        //------------Generar vecindario----------------
        IntervalVector vecino=inicial;
        int iter=0;
        while( cambio && iter<50 ){
            cambio=false;
            for(int i=0;i<inicial.size();i++){
            //--------------Operador de movimiento----------------
            double ruido= RNG::rand(0,1);
            double magnitud= (box[i].ub()-box[i].lb())*0.1;
            ruido=ruido*magnitud;
            vecino[i]=Interval(inicial[i].lb()+ruido,inicial[i].ub()+ruido);
            //--------------funcion de evaluacion----------------
            suma=0;
            for (int i=0;i<sys.nb_ctr;i++){
                suma+=fabs(this->sys.f_ctrs[i].eval(vecino).mid());
            }
            if(suma<mejor){
            //---------------------------------------------------
                mejor=suma;
                inicial=vecino;
                cambio=true;
                break;
            }else{
                vecino=inicial;
            }
        }
            iter++;
        }
        //----------------------------------------------
        return inicial.mid();
    }

        Vector HillClimbing::v4(const IntervalVector& box){
        IntervalVector inicial(box.size());
        IntervalVector mejor_vecino(box.size());
        double suma=0;
        double mejor=0;
        int sizee=box.size();
        double restriccion1=RNG::rand(0,this->sys.nb_ctr-1); // Escoger restriccion aleatoria
        int restriccion=std::round(restriccion1);
        //------------Solucion inicial-----------------
        for(int i=0;i<box.size();i++){
            double random_num = RNG::rand(box[i].lb(),box[i].ub());
            inicial[i]=Interval(random_num,random_num);
        }
        //----------------------------------------------
        // Evaluar la restriccion en la solucion inicial
        for (int i=0;i<sys.nb_ctr;i++){
                mejor+=fabs(this->sys.f_ctrs[i].eval(inicial).mid());
            }
        bool cambio=true;
        //------------Generar vecindario----------------
        IntervalVector vecino=inicial;
        int iter=0;
        while( cambio && iter<50 ){
            cambio=false;
            for(int i=0;i<inicial.size();i++){
            //--------------Operador de movimiento----------------
            double ruido= RNG::rand(0,1);
            double magnitud= (box[i].ub()-box[i].lb())*0.1;
            ruido=ruido*magnitud;
            vecino[i]=Interval(inicial[i].lb()+ruido,inicial[i].ub()+ruido);
            //--------------funcion de evaluacion----------------
            suma=0;
            for (int i=0;i<sys.nb_ctr;i++){
                suma+=fabs(this->sys.f_ctrs[i].eval(vecino).mid());
            }
            if(suma<mejor){
            //---------------------------------------------------
                mejor=suma;
                mejor_vecino=vecino;
                vecino=inicial;
                cambio=true;
            }else{
                vecino=inicial;
            }
        }
            inicial=mejor_vecino;
            iter++;
        }
        //----------------------------------------------
        return inicial.mid();
    }
}