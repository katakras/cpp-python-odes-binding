cmake_minimum_required(VERSION 3.0.0)
project(${TEST_PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE CPP_SOURCES ./*.cpp)
add_executable(${PROJECT_NAME} ${CPP_SOURCES})

macro(add_cpp_test test_path)
    set(TEST_NAME ${test_path})
    add_test(${TEST_NAME} ${PROJECT_NAME} --run_test=${TEST_NAME})
endmacro()

add_cpp_test(matrices/matrix_creation)
add_cpp_test(matrices/matrix_resizing)
add_cpp_test(systems/exponential_system_evaluation)
add_cpp_test(systems/central_force_system_evaluation)
add_cpp_test(solvers/euler_solver)
add_cpp_test(solvers/kutta3_solver)

set(DYLIB_FOLDER "../../build/lib")
target_link_libraries(${PROJECT_NAME} ${LIB_PROJECT_NAME})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
