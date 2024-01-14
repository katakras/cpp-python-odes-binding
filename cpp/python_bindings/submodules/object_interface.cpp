#include "python_bindings/submodules/object_interface.hpp"

#include "python_bindings/common/object_cache.hpp"


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

PyObject* uint_vector_to_python::convert(std::vector<size_t> const& v)
{
    boost::python::list result;
    for(const auto i : v)
    {
        result.append(i);
    }
    return boost::python::incref(result.ptr());
}
