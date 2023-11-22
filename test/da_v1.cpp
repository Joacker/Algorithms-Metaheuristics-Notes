#include <vector>
#include <random>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <functional>
#include <lbfgs.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>

class VisitingDistribution {
    
    double tail_limit = 1e8;
    double min_visit_bound = 1e-10;
    std::vector<double> lower_bound;
    std::vector<double> upper_bound;
    std::vector<double> b_range;
    double qv;
    std::mt19937 rs; // Generador de números aleatorios
    double x_gauss;
    double y_gauss;
    double s_gauss;
    double root_gauss;

public:
    VisitingDistribution(const std::vector<double>& lb, 
                         const std::vector<double>& ub, 
                         double qv, 
                         unsigned seed)
        : lower_bound(lb), upper_bound(ub), qv(qv), rs(seed) {
        // Calcular b_range
        for (size_t i = 0; i < lb.size(); ++i) {
            b_range.push_back(ub[i] - lb[i]);
        }
    }

    std::vector<double> visiting(const std::vector<double>& x, int step, double temperature) {
        size_t dim = x.size();
        std::vector<double> x_visit(dim);
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        if (step < dim) {
            // Cambiando todas las coordenadas con un nuevo valor de visita
            for (size_t i = 0; i < dim; ++i) {
                double visit = visit_fn(temperature);
                // Aplicar límites de la cola
                if (visit > tail_limit) {
                    visit = tail_limit * distribution(rs);
                } else if (visit < -tail_limit) {
                    visit = -tail_limit * distribution(rs);
                }
                x_visit[i] = visit + x[i];

                // Aplicar ajustes de rango y límites
                double a = x_visit[i] - lower_bound[i];
                double b = std::fmod(a, b_range[i]) + b_range[i];
                x_visit[i] = std::fmod(b, b_range[i]) + lower_bound[i];
                if (std::fabs(x_visit[i] - lower_bound[i]) < min_visit_bound) {
                    x_visit[i] += min_visit_bound;
                }
            }
        } else {
            // Cambiando solo una coordenada a la vez basado en el paso de la cadena de Markov
            x_visit = x; // Copiar x a x_visit
            double visit = visit_fn(temperature);
            // Aplicar límites de la cola
            if (visit > tail_limit) {
                visit = tail_limit * distribution(rs);
            } else if (visit < -tail_limit) {
                visit = -tail_limit * distribution(rs);
            }
            size_t index = step - dim;
            x_visit[index] += visit;

            // Aplicar ajustes de rango y límites
            double a = x_visit[index] - lower_bound[index];
            double b = std::fmod(a, b_range[index]) + b_range[index];
            x_visit[index] = std::fmod(b, b_range[index]) + lower_bound[index];
            if (std::fabs(x_visit[index] - lower_bound[index]) < min_visit_bound) {
                x_visit[index] += min_visit_bound;
            }
        }

        return x_visit;
    }
    
    double visit_fn(double temperature) {
        // Implementación de la lógica de visit_fn
        double factor1 = std::exp(std::log(temperature) / (qv - 1.0));
        double factor2 = std::exp((4.0 - qv) * std::log(qv - 1.0));
        double factor3 = std::exp((2.0 - qv) * std::log(2.0) / (qv - 1.0));
        double factor4 = std::sqrt(M_PI) * factor1 * factor2 / (factor3 * (3.0 - qv));
        double factor5 = 1.0 / (qv - 1.0) - 0.5;
        double d1 = 2.0 - factor5;
        double factor6 = M_PI * (1.0 - factor5) / std::sin(M_PI * (1.0 - factor5)) / std::exp(gammal(d1));
        double sigmax = std::exp(-(qv - 1.0) * std::log(factor6 / factor4) / (3.0 - qv));
        double x = sigmax * gaussian_fn(1);
        double y = gaussian_fn(0);
        double den = std::exp((qv - 1.0) * std::log((std::fabs(y))) / (3.0 - qv));
        return x / den;
    }

    double gaussian_fn(int axis) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        if (axis == 1) {
            bool enter = true;
            while (enter || (s_gauss <= 0 || s_gauss >= 1)) {
                enter = false;
                double sample1 = distribution(rs);
                x_gauss = sample1 * 2.0 - 1.0;
                double sample2 = distribution(rs);
                y_gauss = sample2 * 2.0 - 1.0;
                s_gauss = x_gauss * x_gauss + y_gauss * y_gauss;
            }
            root_gauss = std::sqrt(-2.0 / s_gauss * std::log(s_gauss));
            return root_gauss * y_gauss;
        } else {
            return root_gauss * x_gauss;
        }
    }


};

const double BIG_VALUE = 1e16;

class EnergyState {

public:
    static const int MAX_REINIT_COUNT = 1000;
    double ebest;
    double current_energy;
    std::vector<double> current_location;
    std::vector<double> xbest;
    std::vector<double> lower;
    std::vector<double> upper;
    std::mt19937 rs; // Generador de números aleatorios
    EnergyState(const std::vector<double>& lower, const std::vector<double>& upper, unsigned seed)
    : lower(lower), upper(upper), ebest(std::numeric_limits<double>::infinity()), current_energy(std::numeric_limits<double>::infinity()), rs(seed) {}

    void reset(std::function<double(const std::vector<double>&)> func, const std::vector<double>* x0 = nullptr) {
        if (x0 == nullptr) {
            current_location = random_vector();
        } else {
            current_location = *x0;
        }

        int reinit_counter = 0;
        bool init_error = true;
        while (init_error) {
            current_energy = func(current_location);

            if (!std::isfinite(current_energy)) {
                if (++reinit_counter >= MAX_REINIT_COUNT) {
                    throw std::runtime_error("Function creates NaN or infinity values.");
                }
                current_location = random_vector();
            } else {
                init_error = false;
            }

            if (std::isinf(ebest)) {
                ebest = current_energy;
                xbest = current_location;
            }
        }
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "Current: " << current_energy << "@" << vec_to_string(current_location)
            << " Best: " << ebest << "@" << vec_to_string(xbest);
        return oss.str();
    }

private:
    std::vector<double> random_vector() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        std::vector<double> vec(lower.size());
        for (size_t i = 0; i < lower.size(); ++i) {
            vec[i] = lower[i] + dist(rs) * (upper[i] - lower[i]);
        }
        return vec;
    }

    static std::string vec_to_string(const std::vector<double>& vec) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) {
                oss << ", ";
            }
            oss << vec[i];
        }
        oss << "]";
        return oss.str();
    }
};

class ObjectiveFunWrapper {

public:
    std::function<double(const std::vector<double>&)> func;
    std::vector<double> lower;
    std::vector<double> upper;
    double eps = 1e-6; // Precisión para el cálculo del gradiente
    size_t ls_max_iter = 1000;
    size_t nb_fun_call = 0;
    ObjectiveFunWrapper(const std::function<double(const std::vector<double>&)>& func,
                        const std::vector<std::pair<double, double>>& bounds)
        : func(func) {
        for (const auto& bound : bounds) {
            lower.push_back(bound.first);
            upper.push_back(bound.second);
        }
        // Puedes ajustar ls_max_iter según tus necesidades
    }

    double func_wrapper(const std::vector<double>& x) {
        nb_fun_call++;
        return func(x); // Llama directamente a la función objetivo
    }
    static double evaluate(void *instance, 
                           const lbfgsfloatval_t *x, 
                           lbfgsfloatval_t *g, 
                           const int n, 
                           const lbfgsfloatval_t step) {
        // Convertir el puntero 'instance' al tipo correcto
        ObjectiveFunWrapper* wrapper = reinterpret_cast<ObjectiveFunWrapper*>(instance);

        // Convertir 'x' a un vector de doubles
        std::vector<double> vx(x, x + n);

        // Evaluar la función objetivo
        double fx = wrapper->func(vx);

        // Calcular el gradiente
        for (int i = 0; i < n; ++i) {
            std::vector<double> x1 = vx, x2 = vx;
            double respl = wrapper->eps, respr = wrapper->eps;
            x1[i] = std::min(x1[i] + respr, wrapper->upper[i]);
            x2[i] = std::max(x2[i] - respl, wrapper->lower[i]);
            double f1 = wrapper->func(x1);
            double f2 = wrapper->func(x2);
            g[i] = (f1 - f2) / (respr + respl);
        }

        return fx;
    }

    std::pair<double, std::vector<double>> localSearch(const std::vector<double>& x0) {
        int n = x0.size();
        lbfgsfloatval_t* x = lbfgs_malloc(n);
        if (x == nullptr) {
            throw std::runtime_error("LBFGS malloc failed");
        }

        for (int i = 0; i < n; i++) {
            x[i] = x0[i];
        }

        lbfgs_parameter_t param;
        lbfgs_parameter_init(&param);
        param.max_iterations = ls_max_iter;

        double fx;
        int ret = lbfgs(n, x, &fx, evaluate, nullptr, this, &param);

        std::vector<double> result(x, x + n);
        lbfgs_free(x);

        if (ret == LBFGS_SUCCESS || ret == LBFGS_STOP) {
            return std::make_pair(fx, result);
        } else {
            throw std::runtime_error("LBFGS failed: " + std::to_string(ret));
        }
    }
};

class MarkovChain {

public:
    double qa;
    VisitingDistribution& vd;
    ObjectiveFunWrapper& ofw;
    std::mt19937& rs;
    EnergyState& state;
    int not_improved_idx = 0;
    const int not_improved_max_idx = 1000;
    double temperature_step = 0;
    const int K = 100; // Un valor por defecto, puede ser ajustado

    double emin;
    std::vector<double> xmin;

    MarkovChain(double qa, VisitingDistribution& vd, ObjectiveFunWrapper& ofw, std::mt19937& rs, EnergyState& state)
        : qa(qa), vd(vd), ofw(ofw), rs(rs), state(state), emin(state.current_energy), xmin(state.current_location) {}

    void run(int step, double temperature) {
        temperature_step = temperature / static_cast<double>(step + 1);
        not_improved_idx++;
        int dim = state.current_location.size();
        bool state_improved = false;

        for (int j = 0; j < dim * 2; ++j) {
            std::vector<double> x_visit = vd.visiting(state.current_location, j, temperature);
            double e = ofw.func_wrapper(x_visit); // Cambio a func_wrapper

            if (e < state.current_energy) {
                state.current_energy = e;
                state.current_location = x_visit;
                if (e < state.ebest) {
                    state.ebest = e;
                    state.xbest = x_visit;
                    state_improved = true;
                    not_improved_idx = 0;
                }
            } else {
                double r = std::generate_canonical<double, 10>(rs);
                double pqa_temp = (qa - 1.0) * (e - state.current_energy) / temperature_step + 1.0;
                double pqa = pqa_temp < 0.0 ? 0.0 : std::exp(std::log(pqa_temp) / (1.0 - qa));
                if (r <= pqa) {
                    state.current_energy = e;
                    state.current_location = x_visit;
                }
            }

            if (not_improved_idx >= not_improved_max_idx) {
                if (j == 0 || state.current_energy < emin) {
                    emin = state.current_energy;
                    xmin = state.current_location;
                }
            }
        }

        if (state_improved) {
            localSearch();
        }
    }

    void localSearch() {
        // Decision making for performing a local search
        std::pair<double, std::vector<double>> result;
        bool do_ls = false;

        if (K < 90 * state.current_location.size()) {
            double pls = std::exp(K * (state.ebest - state.current_energy) / temperature_step);
            if (pls >= std::generate_canonical<double, 10>(rs)) {
                do_ls = true;
            }
        }

        if (not_improved_idx >= not_improved_max_idx) {
            do_ls = true;
        }

        if (do_ls) {
            result = ofw.localSearch(state.xbest); // or xmin, depending on your logic
            if (result.first < state.ebest) {
                state.ebest = result.first;
                state.xbest = result.second;
                state.current_energy = result.first;
                state.current_location = result.second;
                not_improved_idx = 0;
            }
        }
    }
};

class SDARunner {

    static const int MAX_REINIT_COUNT = 1000;
    public:
        ObjectiveFunWrapper owf;
        std::mt19937 rs;
        EnergyState es;
        VisitingDistribution vd;
        MarkovChain mc;
        int maxfun, maxsteps;
        double temperature_start;
        bool pure_sa;
       SDARunner(std::function<double(const std::vector<double>&)> fun, 
                     const std::vector<double>& x0, 
                     const std::vector<std::pair<double, double>>& bounds, 
                     unsigned seed, 
                     double temperature_start, double qv, double qa,
                     int maxfun, int maxsteps, bool pure_sa) 
    : owf(bounds, fun), rs(seed), es(lroundl, bounds), vd(lroundl, bounds, qv, rs), mc(qa, vd, owf, rs, es) {
        std::vector<double> lower_bounds, upper_bounds;
        // Inicializar lower_bounds y upper_bounds a partir de bounds
        for (const auto& bound : bounds) {
            lower_bounds.push_back(bound.first);
            upper_bounds.push_back(bound.second);
        }

        this->maxfun = maxfun;
        this->maxsteps = maxsteps;
        this->temperature_start = temperature_start;
        this->pure_sa = pure_sa;

        es.reset(owf, rs, x0);
    }

    void search() {
        bool max_steps_reached = false;
        int _iter = 0;
        double t1 = std::exp((qv - 1) * std::log(2.0)) - 1.0;

        while(!max_steps_reached) {
            for (int i = 0; i < maxsteps; ++i) {
                double s = static_cast<double>(i) + 2.0;
                double t2 = std::exp((qv - 1) * std::log(s)) - 1.0;
                double temperature = temperature_start * t1 / t2;
                _iter++;

                if (_iter == maxsteps) {
                    max_steps_reached = true;
                    break;
                }

                if (temperature < temperature_start) {
                    es.reset(owf, rs);
                    break;
                }

                mc.run(i, temperature);

                if (owf.nb_fun_call >= maxfun) {
                    break;
                }

                if (!pure_sa) {
                    mc.localSearch();
                    if (owf.nb_fun_call >= maxfun) {
                        break;
                    }
                }
            }
        }
    }
};

std::pair<std::vector<double>, double> sda(std::function<double(const std::vector<double>&)> func, 
                                           const std::vector<double>& x0,
                                           const std::vector<std::pair<double, double>>& bounds,
                                           int maxiter = 1000,
                                           // Otros parámetros
                                           double initial_temp = 5230.0, double visit = 2.62, double accept = -5.0,
                                           int maxfun = 1e7, unsigned seed = 0, bool pure_sa = false) {
    SDARunner runner(func, x0, bounds, seed, /* otros parámetros */ initial_temp, visit, accept, maxfun, maxiter, pure_sa);
    runner.search();
    // Devolver los resultados
    return std::make_pair(runner.result.x, runner.result.fun);
}



int main(){
    return 0;
}
