// Base class for classes that are storable in the interface

#ifndef STORABLE_HPP
#define STORABLE_HPP

#include <string>

class Storable
{
public:
    virtual std::string storable_name() const = 0;
};

#endif