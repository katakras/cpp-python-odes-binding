#include <boost/test/unit_test.hpp>

#include "lib/odes.hpp"
#include "lib/systems.hpp"
#include "lib/matrix.hpp"

BOOST_AUTO_TEST_SUITE(solvers)

BOOST_AUTO_TEST_CASE(euler_solver)
{
    const auto &system = std::make_shared<systems::ExponentialSystem>(0.5);
    const auto &solver = solvers::EulerSolver(0.1);
    const auto &ode_results = solver.solve(system, 0.0, std::vector{1.0}, 0.09);

    BOOST_CHECK_EQUAL(ode_results->t().size(), 2u);
    BOOST_CHECK_EQUAL(ode_results->m()->n_rows(), 2u);
    BOOST_CHECK_EQUAL(ode_results->m()->n_cols(), 1u);

    BOOST_CHECK_CLOSE((*ode_results->m())(1u, 0u), 1.0 + 0.1 * (0.5 * 1.0), 1e-8);
}

BOOST_AUTO_TEST_CASE(kutta3_solver)
{
    const auto &system = std::make_shared<systems::ExponentialSystem>(0.5);
    const auto &solver = solvers::Kutta3Solver(0.1);
    const auto &ode_results = solver.solve(system, 0.0, std::vector{1.0}, 0.09);

    BOOST_CHECK_EQUAL(ode_results->t().size(), 2u);
    BOOST_CHECK_EQUAL(ode_results->m()->n_rows(), 2u);
    BOOST_CHECK_EQUAL(ode_results->m()->n_cols(), 1u);

    const double k1 = 0.5;
    const double k2 = 0.5 * (1.0 + 0.5 * 0.1 * k1);
    const double k3 = 0.5 * (1.0 + 0.1 * (-1 * k1 + 2 * k2));

    BOOST_CHECK_CLOSE((*ode_results->m())(1u, 0u), 1.0 + 0.1 * ((1.0 / 6) * k1 + (2.0 / 3) * k2 + (1.0 / 6) * k3), 1e-8);
}

BOOST_AUTO_TEST_SUITE_END()
