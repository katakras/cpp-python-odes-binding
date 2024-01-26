#include "object_cache.hpp"

#include "lib/storable.hpp"

#include <iostream>

namespace object_cache
{

    size_t _id = 0;
    std::unordered_map<size_t, std::shared_ptr<Storable>> _object_map{};

    size_t store_object(const std::shared_ptr<Storable> &p)
    {
        const size_t new_id = ++_id;
        _object_map[new_id] = p;
        return new_id;
    }

}
