
#include <boost/python.hpp>

#include "python_bindings/submodules/matrix.hpp"
#include "python_bindings/submodules/object_interface.hpp"

namespace bp = boost::python;


void object_interface_submodule()
{
    bp::object object_interface_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.object_interface"))));

    bp::scope().attr("object_interface") = object_interface_module;

    bp::scope object_interface_scope = object_interface_module;

    bp::def("object_list", &object_list);
    bp::to_python_converter<std::vector<size_t>, uint_vector_to_python>();
}

BOOST_PYTHON_MODULE(odescppy)
{
    using namespace boost::python;

    bp::object main_module_scope = bp::scope(); //bp::class_<bp::object>("odescppy");

    matrix_submodule();
    object_interface_submodule();
}
