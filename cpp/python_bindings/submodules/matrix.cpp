#include "python_bindings/submodules/matrix.hpp"

#include <boost/python.hpp>

#include "python_bindings/common/submodule_registration.hpp"
#include "python_bindings/common/object_cache.hpp"
#include "lib/matrix.hpp"

namespace
{

    size_t python_array_to_matrix(const boost::python::list &array)
    {
        const size_t n_rows = boost::python::len(array);
        if (n_rows == 0u)
        {
            return object_cache::store_object(std::make_shared<Matrix>(0u, 0u));
        }
        const size_t n_cols = boost::python::len(array[0u]);

        for (size_t i = 1; i < n_cols; ++i)
        {
            if (boost::python::len(boost::python::extract<boost::python::list>((array[i]))) != n_cols)
            {
                throw std::runtime_error("Irregular matrix.");
            }
        }

        const auto &matrix = std::make_shared<Matrix>(n_rows, n_cols);
        for (size_t i_row = 0; i_row < n_rows; ++i_row)
        {
            boost::python::list python_row = boost::python::extract<boost::python::list>(array[i_row]);
            for (size_t i_col = 0; i_col < n_cols; ++i_col)
            {
                (*matrix)(i_row, i_col) = boost::python::extract<double>(python_row[i_col]);
            }
        }
        return object_cache::store_object(matrix);
    }

    boost::python::list matrix_to_python_array(const size_t object_id)
    {
        const auto &matrix = object_cache::get_object<Matrix>(object_id);

        boost::python::list array;
        for (size_t i_row = 0; i_row < matrix->n_rows(); ++i_row)
        {
            boost::python::list array_row;
            const auto &row = (*matrix)[i_row];
            for (size_t i_col = 0; i_col < matrix->n_cols(); ++i_col)
            {
                array_row.append((*row)[i_col]);
            }
            array.append(array_row);
        }
        return array;
    }

}

DEFINE_PYTHON_SUBMODULE(matrix)
{
    namespace bp = boost::python;

    bp::object matrix_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.matrix"))));

    bp::scope().attr("matrix") = matrix_module;

    bp::scope matrix_scope = matrix_module;

    bp::def("python_array_to_matrix", &::python_array_to_matrix);
    bp::def("matrix_to_python_array", &::matrix_to_python_array);

    bp::register_ptr_to_python<std::shared_ptr<Matrix>>();
}
