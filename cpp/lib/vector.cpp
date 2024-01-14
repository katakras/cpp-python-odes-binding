#include "lib/vector.hpp"


std::vector<double>* make_vector(const size_t size, const double initial_value)
{
    return new std::vector<double>(size, initial_value);
}

void vector_set(std::vector<double>* v, const double value, const size_t i)
{
    (*v)[i] = value;
}

double vector_get(std::vector<double> const* const v, const size_t i)
{
    return (*v)[i];
}

size_t vector_size(std::vector<double>* const v)
{
    return v->size();
}

void vector_delete(std::vector<double>* const v)
{
    delete v;
}