#include "python_bindings/submodules/systems.hpp"

#include <boost/python.hpp>

#include "lib/systems.hpp"
#include "python_bindings/common/submodule_registration.hpp"
#include "python_bindings/common/object_cache.hpp"

namespace
{
    size_t make_exponential_system(const double alpha)
    {
        const auto &system = std::make_shared<systems::ExponentialSystem>(alpha);
        return object_cache::store_object(std::shared_ptr<systems::System>(system));
    }

    size_t make_central_force_system(const double F)
    {
        const auto &system = std::make_shared<systems::CentralForceSystem>(F);
        return object_cache::store_object(std::shared_ptr<systems::System>(system));
    }

}

DEFINE_PYTHON_SUBMODULE(systems)
{
    namespace bp = boost::python;

    bp::object systems_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.systems"))));

    bp::scope().attr("systems") = systems_module;

    bp::scope systems_scope = systems_module;

    bp::def("make_exponential_system", &::make_exponential_system);
    bp::def("make_central_force_system", &::make_central_force_system);
}
