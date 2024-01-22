
#include <boost/python.hpp>

#include "python_bindings/common/submodule_registration.hpp"


BOOST_PYTHON_MODULE(odescppy)
{
    namespace bp = boost::python;

    bp::object main_module_scope = bp::scope(); 
    
    for(const auto& sm : SUBMODULES_)
    {
        sm();
    }
}
