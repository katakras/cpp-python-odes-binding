// All systems of equations

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <vector>

#include "lib/macros.hpp"

class Matrix;

namespace systems
{

class System {
public:
    System() = default;
    virtual std::vector<double> f(const double t, const std::vector<double>& x) const = 0;
    virtual std::shared_ptr<Matrix> transform(const std::shared_ptr<Matrix>& m) const;
};

class ExponentialSystem : public System {
public:
    
    ExponentialSystem(const double k);
    std::vector<double> f(const double t, const std::vector<double>& x) const override;

private:

    double k_;

};
EXPORT_FUNCTION ExponentialSystem* const make_ExponentialSystem(const double k);
EXPORT_FUNCTION void delete_ExponentialSystem(ExponentialSystem const* ptr);

class CentralForceSystem : public System {
public:
    
    CentralForceSystem(const double f);
    std::vector<double> f(const double t, const std::vector<double>& x) const override;
    std::shared_ptr<Matrix> transform(const std::shared_ptr<Matrix>& m) const override;

private:
    double f_;
};
EXPORT_FUNCTION CentralForceSystem* const make_CentralForceSystem(const double k);
EXPORT_FUNCTION void delete_CentralForceSystem(CentralForceSystem const* ptr);


}

#endif
