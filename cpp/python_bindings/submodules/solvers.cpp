#include "python_bindings/submodules/solvers.hpp"

#include <boost/python.hpp>

#include "lib/matrix.hpp"
#include "lib/systems.hpp"
#include "lib/odes.hpp"
#include "python_bindings/common/submodule_registration.hpp"
#include "python_bindings/common/object_cache.hpp"

namespace
{

    boost::python::list convert_vector_to_python_list(const std::vector<double> &v)
    {
        boost::python::list result;
        for (auto d : v)
        {
            result.append(d);
        }
        return result;
    }

    boost::python::list convert_matrix_to_python_list(const std::shared_ptr<Matrix> &m)
    {
        boost::python::list result;
        for (size_t i_row = 0; i_row < m->n_rows(); ++i_row)
        {
            boost::python::list row;
            for (size_t i_col = 0; i_col < m->n_cols(); ++i_col)
            {
                row.append((*m)(i_row, i_col));
            }
            result.append(row);
        }
        return result;
    }

    boost::python::list unpack_ode_results(const size_t results_id)
    {
        const auto &results = object_cache::get_object<ODEResults>(results_id);

        boost::python::list result;

        const auto &times = results->t();
        result.append(convert_vector_to_python_list(times));

        const auto &results_matrix = results->m();
        result.append(convert_matrix_to_python_list(results_matrix));

        return result;
    }

    size_t solve_system(const size_t solver_id,
                        const size_t system_id,
                        const double t0,
                        const boost::python::list &x0,
                        const double T)
    {

        const auto &dvector_convert = [](const boost::python::list &v)
        {
            const size_t n = boost::python::len(v);
            std::vector<double> ret(n, 0.0);

            for (size_t i = 0; i < n; ++i)
            {
                ret[i] = boost::python::extract<double>(v[i]);
            }
            return ret;
        };

        const auto &solver = object_cache::get_object<solvers::Solver>(solver_id);
        const auto &system = object_cache::get_object<systems::System>(system_id);
        const auto &result = solver->solve(system, t0, dvector_convert(x0), T);
        return object_cache::store_object(result);
    }

    size_t make_euler_solver(const double dt)
    {
        const auto &solver = std::make_shared<solvers::EulerSolver>(dt);
        return object_cache::store_object(
            std::shared_ptr<solvers::Solver>{solver});
    }
}

DEFINE_PYTHON_SUBMODULE(solvers)
{
    namespace bp = boost::python;

    bp::object solvers_module(bp::handle<>(bp::borrowed(PyImport_AddModule("odescppy.solvers"))));

    bp::scope().attr("solvers") = solvers_module;

    bp::scope solvers_scope = solvers_module;

    bp::def("solve_system", &::solve_system);
    bp::def("make_euler_solver", &::make_euler_solver);
    bp::def("unpack_ode_results", &::unpack_ode_results);
}
