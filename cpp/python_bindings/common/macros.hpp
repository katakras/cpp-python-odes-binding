#ifndef PY_BINDINGS_MACROS_HPP
#define PY_BINDINGS_MACROS_HPP

#define DECLARE_PYTHON_SUBMODULE(name) \
    void name##_submodule();

#define DEFINE_PYTHON_SUBMODULE(name) \
namespace \
{ \
    struct AddSubmodule \
    { \
        AddSubmodule() \
        { \
            SUBMODULES_.push_back(&name##_submodule); \
        } \
    }; \
    static AddSubmodule as_; \
} \
    void name##_submodule()

#endif