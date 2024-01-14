#include "python_bindings/submodules/matrix.hpp"

#include "python_bindings/common/object_cache.hpp"

#include "lib/matrix.hpp"

#include <boost/python.hpp>

namespace 
{
size_t get_matrix_n_rows(const std::shared_ptr<Matrix>& m)
{
    return m->n_rows();
}

size_t make_matrix(const size_t n_rows, const size_t n_cols)
{
    const auto& ret = std::make_shared<Matrix>(n_rows, n_cols);
    return object_cache::store_object<Matrix>(ret);
}
}


void matrix_submodule()
{
    namespace bp = boost::python;

    bp::object matrix_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.matrix"))));

    bp::scope().attr("matrix") = matrix_module;

    bp::scope matrix_scope = matrix_module;

    bp::def("get_matrix_n_rows", &::get_matrix_n_rows);
    //bp::def<size_t (*) (const std::shared_ptr<Matrix>&)>("get_matrix_n_rows", &get_matrix_n_rows);
    bp::def("make_matrix", &::make_matrix);

    bp::register_ptr_to_python<std::shared_ptr<Matrix>>();
}