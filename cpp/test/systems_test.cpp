#include <boost/test/unit_test.hpp>

#include "lib/systems.hpp"

BOOST_AUTO_TEST_SUITE(systems)

BOOST_AUTO_TEST_CASE(exponential_system_evaluation)
{
    const auto &system = systems::ExponentialSystem(0.5);
    const std::vector<double> x(system.f(0.0, std::vector{1.0}));

    BOOST_CHECK_EQUAL(x.size(), 1u);
    BOOST_CHECK_CLOSE(x[0u], 0.5, 1e-13);
}

BOOST_AUTO_TEST_CASE(central_force_system_evaluation)
{
    const auto &system = systems::CentralForceSystem(0.5);
    const std::vector<double> x(system.f(0.0, std::vector{1.0, 0.0, 0.0, 0.0}));

    BOOST_CHECK_EQUAL(x.size(), 4u);
    BOOST_CHECK_CLOSE(x[0u], 0.0, 1e-13);
    BOOST_CHECK_CLOSE(x[1u], 0.0, 1e-13);
    BOOST_CHECK_CLOSE(x[2u], 0.5, 1e-13);
    BOOST_CHECK_CLOSE(x[3u], 0.0, 1e-13);
}

BOOST_AUTO_TEST_SUITE_END()
