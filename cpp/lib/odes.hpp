// ODE solvers

#ifndef ODES_HPP
#define ODES_HPP

#include <vector>

#include "lib/macros.hpp"
#include "lib/systems.hpp"

class Matrix;

class ODEResults
{
public:
    ODEResults(std::vector<double> &&t, std::shared_ptr<Matrix> m);

    const std::vector<double> &t() const
    {
        return t_;
    }
    const std::shared_ptr<Matrix> &m() const
    {
        return m_;
    }

public:
    std::vector<double> t_;
    std::shared_ptr<Matrix> m_;
};

namespace solvers
{

    class Solver
    {
    public:
        virtual std::shared_ptr<ODEResults> solve(const std::shared_ptr<systems::System> &system,
                                                  const double t0,
                                                  const std::vector<double> &x0,
                                                  const double T) const = 0;
    };

    class EulerSolver : public Solver
    {
    public:
        EulerSolver(const double dt);
        std::shared_ptr<ODEResults> solve(const std::shared_ptr<systems::System> &system,
                                          const double t0,
                                          const std::vector<double> &x0,
                                          const double T) const override;

    private:
        double dt_;
    };

} // namespace solvers

#endif
