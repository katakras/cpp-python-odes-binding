// Utilities for the vector class

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>

#include "lib/macros.hpp"


EXPORT_FUNCTION std::vector<double>* make_vector(const size_t size, const double initial_value);
EXPORT_FUNCTION void vector_set(std::vector<double>* v, const double value, const size_t i);
EXPORT_FUNCTION double vector_get(std::vector<double> const* const v, const size_t i);
EXPORT_FUNCTION size_t vector_size(std::vector<double>* const v);
EXPORT_FUNCTION void vector_delete(std::vector<double>* const v);

#endif