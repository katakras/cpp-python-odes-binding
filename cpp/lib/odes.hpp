// ODE solvers

#ifndef ODES_HPP
#define ODES_HPP

#include <vector>

#include "macros.hpp"
#include "systems.hpp"

class Matrix;

class ODEResults
{
public:
    ODEResults(std::vector<double>&& t, std::shared_ptr<Matrix> m);

    const std::vector<double>& t() const { return t_; }
    const std::shared_ptr<Matrix>& m() const { return m_; }

public:
    std::vector<double> t_;
    std::shared_ptr<Matrix> m_;

};


EXPORT_FUNCTION std::vector<double> const* ODEResults_t_address(ODEResults const* ptr);
EXPORT_FUNCTION Matrix const* ODEResults_m_address(ODEResults const* ptr);
EXPORT_FUNCTION void delete_ODEResults(ODEResults const* ptr);

namespace solvers
{
EXPORT_FUNCTION ODEResults const* euler(systems::System* const system_ptr, const double t0, std::vector<double> const* x0, const double T, const double dt);
}

#endif
