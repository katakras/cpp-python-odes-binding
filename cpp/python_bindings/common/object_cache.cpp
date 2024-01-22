#include "object_cache.hpp"

#include "lib/matrix.hpp"

#include <iostream>

namespace object_cache
{

size_t _id = 0;
std::unordered_map<size_t, std::any> _object_map{};

}
