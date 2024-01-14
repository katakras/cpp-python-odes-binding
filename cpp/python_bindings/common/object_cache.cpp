#include "object_cache.hpp"

#include "lib/matrix.hpp"

#include <iostream>

namespace object_cache
{

size_t _id = 0;
std::unordered_map<size_t, std::any> _object_map{};


template <typename T>
std::shared_ptr<T> get_object(const size_t id)
{
    auto any_res = _object_map.at(id);
    try 
    {
        const auto& result = std::any_cast<std::shared_ptr<T>>(any_res);
        return result;
    } catch (const std::bad_any_cast& e)
    {
        throw GetObjectException(e.what());
    }
}

template <typename T>
size_t store_object(const std::shared_ptr<T>& p)
{
    const size_t new_id = ++_id;
    _object_map[new_id] = p;
    return new_id; 
}

template size_t store_object<Matrix>(const std::shared_ptr<Matrix>&);

}
