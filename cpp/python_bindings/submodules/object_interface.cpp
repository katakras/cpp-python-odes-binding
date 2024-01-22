#include "python_bindings/submodules/object_interface.hpp"

#include <boost/python.hpp>

#include "python_bindings/common/submodule_registration.hpp"
#include "python_bindings/common/object_cache.hpp"


namespace 
{

struct uint_vector_to_python
{
    static PyObject* convert(std::vector<size_t> const& v)
    {
        boost::python::list result;
        for(const auto i : v)
        {
            result.append(i);
        }
        return boost::python::incref(result.ptr());
    }
};

std::vector<size_t> object_list()
{
    std::vector<size_t> ret;
        ret.reserve(object_cache::_object_map.size());
        std::transform(object_cache::_object_map.begin(), 
            object_cache::_object_map.end(), 
            std::back_inserter(ret), 
            [](const auto& it){ return it.first; });
        return ret;
}

bool object_delete(const size_t object_id)
{
    const auto& map_it = object_cache::_object_map.find(object_id);
    if(map_it == object_cache::_object_map.end())
    {
        return false;
    }
    else 
    {
        object_cache::_object_map.erase(object_id);
        return true;
    }
}

}


DEFINE_PYTHON_SUBMODULE(object_interface)
{
    namespace bp = boost::python;

    bp::object object_interface_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.object_interface"))));

    bp::scope().attr("object_interface") = object_interface_module;

    bp::scope object_interface_scope = object_interface_module;

    bp::def("object_list", &::object_list);
    bp::to_python_converter<std::vector<size_t>, ::uint_vector_to_python>();
    bp::def("object_delete", &::object_delete);
}
