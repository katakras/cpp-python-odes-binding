#ifndef PY_BINDINGS_OBJECT_CACHE_HPP
#define PY_BINDINGS_OBJECT_CACHE_HPP

#include <any>
#include <memory>
#include <unordered_map>
#include <string>

namespace object_cache
{

class GetObjectException : public std::exception
{
public:
    GetObjectException(std::string err) : err_(std::move(err)) {};
    const char* what() const noexcept override { return err_.c_str(); };
private:
    std::string err_;
};


extern size_t _id;
extern std::unordered_map<size_t, std::any> _object_map;

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

}

#endif