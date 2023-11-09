#include "/test/dual-annealing/include/chain.hpp"
#include "/test/dual-annealing/third_party/pcg-cpp/include/pcg_random.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <random>

using namespace DualAnnealing;
using DualAnnealing::tsallis_distribution_t;
tsallis_distribution_t tsallis_dist(1.5, 1.0); // Inicializa la distribución con q y una temperatura inicial
struct to_range_t {
    float min;
    float max;

    auto operator()(float const x) const -> float
    {
        auto const length = max - min;
        auto const delta =
            std::fmod(std::fmod(x - min, length) + length, length);
        return min + delta;
    }
};

struct rastrigin_t {
    to_range_t _wrap{-5.12f, 5.12f};

    auto value(gsl::span<float const> x) const -> float
    {
        constexpr auto A = 10.0;
        auto           E = 0.0;
        for (auto i = size_t{0}; i < x.size(); ++i) {
            auto const a = static_cast<double>(x[i]);
            E += a * a - A * std::cos(2.0 * M_PI * a);
        }
        E += A * x.size();
        return E;
    }

    auto wrap(float const x) const -> float { return _wrap(x); }

    auto value_and_gradient(gsl::span<float const> x, gsl::span<float> g) const
        -> double
    {
        constexpr auto A = 10.0;
        for (auto i = size_t{0}; i < x.size(); ++i) {
            auto const a = static_cast<double>(x[i]);
            g[i]         = static_cast<float>(
                2 * a + 2 * M_PI * A * std::sin(2.0 * M_PI * a));
        }
        return value(x);
    }
#if 0
    auto operator()(size_t const i, float const x, float const value,
                    gsl::span<float const> xs) const -> float
    {
        auto const shift = 0.0f;
        auto       E     = value;
        E -=
            std::pow(xs[i] - shift, 2.0f)
            - 10.0f
                  * std::cos(2.0f * static_cast<float>(M_PI) * (xs[i] - shift));
        E += std::pow(x - shift, 2.0f)
             - 10.0f * std::cos(2.0f * static_cast<float>(M_PI) * (x - shift));
        return E;
    }
#endif
};

int main(int argc, char* argv[])
{
    // if (argc != 2) {
    //     std::fprintf(stderr, "Expected 1 argument: <L>\n");
    //     return EXIT_FAILURE;
    // }
    // auto const length = std::atol(argv[1]);

    using std::begin, std::end;
    auto const params = dual_annealing::param_t{/*q_V=*/2.67,
                                                /*q_A=*/-5.0,
                                                /*t_0=*/10.0,
                                                // /*t_0=*/5300.0,
                                                /*num_iter=*/1000,
                                                /*patience=*/20};

    pcg32 generator{1230045};
    auto  energy_fn = rastrigin_t{};

    std::vector<float> xs(100);
    for (auto& x : xs) {
        x = std::uniform_real_distribution<float>{-1.0f, 3.0f}(generator);
    }

    std::cout << "Before: f([";
    std::copy(begin(xs), end(xs),
              std::ostream_iterator<float>{std::cout, ", "});
    std::cout << "]) = " << energy_fn.value(xs) << '\n';

    auto local_search_parameters  = tcm::lbfgs::lbfgs_param_t{};
    local_search_parameters.x_tol = 1e-5;
    auto const result             = dual_annealing::minimize(
        energy_fn, xs, params, local_search_parameters, generator);

    std::cout << "After : f([";
    std::copy(begin(xs), end(xs),
              std::ostream_iterator<float>{std::cout, ", "});
    std::cout << "]) = " << result.func << '\n';
    std::cout << "Number iterations: " << result.num_iter << '\n'
              << "Number function evaluations: " << result.num_f_evals << '\n'
              << "Acceptance: " << result.acceptance << '\n';
    return EXIT_SUCCESS;
}
