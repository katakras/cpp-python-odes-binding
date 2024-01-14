#include "lib/systems.hpp"

#include <cassert>
#include <cmath>

#include "lib/matrix.hpp"

namespace systems
{

// * System *
std::shared_ptr<Matrix> System::transform(const std::shared_ptr<Matrix>& m) const
{
    return m;
}
// ***

// * Exponential *
ExponentialSystem::ExponentialSystem(const double k) : System(), k_(k)
{
}

std::vector<double> ExponentialSystem::f(const double t, const std::vector<double>& x) const 
{
    return std::vector{k_ * x[0]};
}

ExponentialSystem* const make_ExponentialSystem(const double k)
{
    return new ExponentialSystem(k);
}

void delete_ExponentialSystem(ExponentialSystem const* ptr)
{
    delete ptr;
}
// ***

// * Central force *
CentralForceSystem::CentralForceSystem(const double f) : System(), f_(f)
{
}

std::vector<double> CentralForceSystem::f(const double t, const std::vector<double>& x) const
{
    return std::vector{x[2], x[3], f_ / (x[0] * x[0]), 0.0};
}

namespace 
{
    void convert_polar_to_cartesian_in_place(double& x1, double& x2, double& v1, double& v2)
    {
        // on start, x1 = r, x2 = theta
        // v1 = r', v2 = theta'

        const double r = x1;
        const double cos_theta = cos(x2);
        const double sin_theta = sin(x2);

        const double dr = v1;
        const double dtheta = v2;

        x1 = r * cos_theta;
        x2 = r * sin_theta;

        v1 = dr * cos_theta - r * dtheta * sin_theta;
        v2 = dr * sin_theta + r * dtheta * cos_theta;
    }
}

std::shared_ptr<Matrix> CentralForceSystem::transform(const std::shared_ptr<Matrix>& m) const
{
    const size_t n_rows = m->n_rows();
    const size_t n_cols = m->n_cols();

    assert(n_cols == 4u);

    for(size_t i_row = 0; i_row < n_rows; ++i_row)
    {
        auto row = (*m)[i_row];
        convert_polar_to_cartesian_in_place((*row)[0u], (*row)[1u], (*row)[2u], (*row)[3u]);
    }
    return m;
}

CentralForceSystem* const make_CentralForceSystem(const double f)
{
    return new CentralForceSystem(f); 
}

void delete_CentralForceSystem(CentralForceSystem const* ptr)
{
    delete ptr;
}
// ***
}