// ODE solvers

#ifndef ODES_HPP
#define ODES_HPP

#include <vector>

#include "lib/macros.hpp"
#include "lib/systems.hpp"

class Matrix;

class ODEResults : public Storable
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

    std::string storable_name() const override { return "ODEResults"; }

private:
    std::vector<double> t_;
    std::shared_ptr<Matrix> m_;
};

namespace solvers
{

    class Solver : public Storable
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

        std::string storable_name() const override { return "EulerSolve"; }

    private:
        double dt_;
    };

    class Kutta3Solver : public Solver
    {
    public:
        Kutta3Solver(const double dt);
        std::shared_ptr<ODEResults> solve(const std::shared_ptr<systems::System> &system,
                                          const double t0,
                                          const std::vector<double> &x0,
                                          const double T) const override;

        std::string storable_name() const override { return "Kutta3Solver"; }

    private:
        double dt_;
    };

} // namespace solvers

#endif
