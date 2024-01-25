// All systems of equations

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <vector>

#include "lib/macros.hpp"

class Matrix;

namespace systems
{

    class System
    {
    public:
        System() = default;
        virtual std::vector<double> f(const double t, const std::vector<double> &x) const = 0;
        virtual std::shared_ptr<Matrix> transform(const std::shared_ptr<Matrix> &m) const;
    };

    class ExponentialSystem : public System
    {
    public:
        ExponentialSystem(const double k);
        std::vector<double> f(const double t, const std::vector<double> &x) const override;

    private:
        double k_;
    };

    class CentralForceSystem : public System
    {
    public:
        CentralForceSystem(const double f);
        std::vector<double> f(const double t, const std::vector<double> &x) const override;
        std::shared_ptr<Matrix> transform(const std::shared_ptr<Matrix> &m) const override;

    private:
        double f_;
    };
}

#endif
