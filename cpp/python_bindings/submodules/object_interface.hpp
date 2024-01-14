#ifndef PY_BINDINGS_OBJECT_INTERFACE_HPP
#define PY_BINDINGS_OBJECT_INTERFACE_HPP

#include <vector>

#include <boost/python.hpp>

std::vector<size_t> object_list();

struct uint_vector_to_python
{
    static PyObject* convert(std::vector<size_t> const& v);
};

#endif