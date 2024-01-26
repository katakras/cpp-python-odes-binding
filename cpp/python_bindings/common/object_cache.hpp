#ifndef PY_BINDINGS_OBJECT_CACHE_HPP
#define PY_BINDINGS_OBJECT_CACHE_HPP

#include <memory>
#include <unordered_map>
#include <string>

#include "lib/storable.hpp"

namespace object_cache
{

    class GetObjectException : public std::exception
    {
    public:
        GetObjectException(std::string err) : err_(std::move(err)){};
        const char *what() const noexcept override { return err_.c_str(); };

    private:
        std::string err_;
    };

    extern size_t _id;
    extern std::unordered_map<size_t, std::shared_ptr<Storable>> _object_map;

    template <typename T>
    std::shared_ptr<T> get_object(const size_t id)
    {
        const auto &res = _object_map.at(id);

        const auto &ret = std::dynamic_pointer_cast<T>(res);
        if (ret)
        {
            return ret;
        }
        else
        {
            throw std::runtime_error("Wrong object type.");
        }
    }

    size_t store_object(const std::shared_ptr<Storable> &p);

}

#endif