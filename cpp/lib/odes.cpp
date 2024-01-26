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

    std::vector<double> operator*(const double k, std::vector<double> &&v)
    {
        std::transform(v.begin(), v.end(), v.begin(), [&k](const double vn)
                       { return k * vn; });
        return v;
    }

    std::vector<double> operator+(const std::vector<double> &vl, std::vector<double> &&vr)
    {
        for (size_t i = 0; i < vl.size(); ++i)
        {
            vr[i] += vl[i];
        }
        return vr;
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

        for (size_t i_step = 1; i_step < n_steps + 1; ++i_step)
        {
            const auto &prev_x = (*result)[i_step - 1u]->data();
            result->insert_row(add_vectors(prev_x, product_by_scalar(dt_, system->f(t0 + i_step * dt_, prev_x))), i_step);
            t[i_step] = t0 + i_step * dt_;
        }

        const auto &transformed_result = system->transform(result);

        return std::make_shared<ODEResults>(std::move(t), transformed_result);
    }

    ODEResults const *euler(systems::System *const system_ptr, const double t0, std::vector<double> const *x0, const double T, const double dt)
    {
        const size_t system_size = x0->size();
        const size_t n_steps = static_cast<size_t>((T - t0) / dt + 1);
        const auto &result = std::make_shared<Matrix>(n_steps + 1u, system_size);
        result->insert_row(*x0, 0u);

        std::vector<double> t(n_steps + 1u, t0);

        for (size_t i_step = 1; i_step < n_steps + 1; ++i_step)
        {
            const auto &prev_x = (*result)[i_step - 1u]->data();
            result->insert_row(add_vectors(prev_x, product_by_scalar(dt, system_ptr->f(t0 + i_step * dt, prev_x))), i_step);
            t[i_step] = t0 + i_step * dt;
        }

        const auto &transformed_result = system_ptr->transform(result);

        return new ODEResults(std::move(t), transformed_result);
    }

}