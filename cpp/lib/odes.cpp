#include "lib/odes.hpp"

#include <variant>
#include <algorithm>

#include "lib/matrix.hpp"

namespace
{
    std::vector<double> product_by_scalar(const double k, std::vector<double> &&v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [&k](const double vn)
                       { return k * vn; });
        return v;
    }

    std::vector<double> add_vectors(const std::vector<double> &vl, std::vector<double> &&vr)
    {
        for (size_t i = 0; i < vl.size(); ++i)
        {
            vr[i] += vl[i];
        }
        return vr;
    }

    std::vector<double> operator*(const double k, const std::vector<double> &v)
    {
        std::vector<double> ret;
        ret.reserve(v.size());
        std::transform(v.begin(), v.end(), std::back_inserter(ret), [&k](const double vn)
                       { return k * vn; });
        return std::move(ret);
    }

    std::vector<double> operator*(const double k, std::vector<double> &&v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [&k](const double vn)
                       { return k * vn; });
        return std::move(v);
    }

    std::vector<double> operator+(const std::vector<double> &vl, std::vector<double> &&vr)
    {
        if (vl.size() != vr.size())
        {
            throw std::runtime_error("Operation with wrong vector sizes.");
        }
        for (size_t i = 0; i < vl.size(); ++i)
        {
            vr[i] += vl[i];
        }
        return std::move(vr);
    }
}

ODEResults::ODEResults(std::vector<double> &&t, std::shared_ptr<Matrix> m) : t_(t), m_(std::move(m))
{
}

namespace solvers
{

    EulerSolver::EulerSolver(const double dt)
        : dt_(dt)
    {
    }

    std::shared_ptr<ODEResults> EulerSolver::solve(const std::shared_ptr<systems::System> &system,
                                                   const double t0,
                                                   const std::vector<double> &x0,
                                                   const double T) const
    {
        const size_t system_size = x0.size();
        const size_t n_steps = static_cast<size_t>((T - t0) / dt_ + 1);
        const auto &result = std::make_shared<Matrix>(n_steps + 1u, system_size);
        result->insert_row(x0, 0u);

        std::vector<double> t(n_steps + 1u, t0);

        for (size_t i_step = 1; i_step < n_steps + 1u; ++i_step)
        {
            const auto &prev_x = (*result)[i_step - 1u]->data();
            result->insert_row(prev_x + dt_ * system->f(t0 + i_step * dt_, prev_x), i_step);
            t[i_step] = t0 + i_step * dt_;
        }

        const auto &transformed_result = system->transform(result);

        return std::make_shared<ODEResults>(std::move(t), transformed_result);
    }

    Kutta3Solver::Kutta3Solver(const double dt)
        : dt_(dt)
    {
    }

    std::shared_ptr<ODEResults> Kutta3Solver::solve(const std::shared_ptr<systems::System> &system,
                                                    const double t0,
                                                    const std::vector<double> &x0,
                                                    const double T) const
    {
        const size_t system_size = x0.size();
        const size_t n_steps = static_cast<size_t>((T - t0) / dt_ + 1);
        const auto &result = std::make_shared<Matrix>(n_steps + 1u, system_size);
        result->insert_row(x0, 0u);

        std::vector<double> t(n_steps + 1u, t0);

        for (size_t i_step = 1; i_step < n_steps + 1u; ++i_step)
        {
            const double current_t = t0 + i_step * dt_;
            const auto &prev_x = (*result)[i_step - 1u]->data();
            std::vector<std::vector<double>> k(3u);
            k[0] = system->f(current_t, prev_x);
            k[1] = system->f(current_t + dt_ * 0.5, prev_x + (0.5 * dt_) * k[0]);
            k[2] = system->f(current_t + dt_, prev_x + dt_ * (-1 * k[0] + 2 * k[1]));

            auto next_x = prev_x + dt_ * ((1.0 / 6) * std::move(k[0]) + (2.0 / 3) * std::move(k[1]) + (1.0 / 6) * std::move(k[2]));
            result->insert_row(std::move(next_x), i_step);
            t[i_step] = current_t;
        }

        const auto &transformed_result = system->transform(result);
        return std::make_shared<ODEResults>(std::move(t), transformed_result);
    }

}