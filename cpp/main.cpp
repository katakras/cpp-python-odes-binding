
#include "systems.hpp"
#include "odes.hpp"
#include "vector.hpp"

int main()
{
    auto system = systems::make_ExponentialSystem(1.0);
    auto x0 = make_vector(1u, 1.0);
    vector_set(x0, 1.0, 0u);

    auto ode_result = solvers::euler(system, 0.0, x0, 10.0, 0.1);
    delete_ExponentialSystem(system);

    auto t_ptr = ODEResults_t_address(ode_result);
    delete t_ptr;

    auto m_ptr = ODEResults_m_address(ode_result);

    delete_ODEResults(ode_result);

}