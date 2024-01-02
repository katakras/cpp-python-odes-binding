cmake_minimum_required(VERSION 3.0.0)
project(CPPyODEsTest VERSION 0.1.0 LANGUAGES C CXX)

set(LIB_HEADERS "../lib")
include_directories(${LIB_HEADERS})

set(CMAKE_CXX_STANDARD 20)

add_executable(CPPyODEsTest main.cpp)

set(DYLIB_FOLDER "../../build/lib")
#target_link_libraries(CPPyODEsTest GTest::GTest)
target_link_libraries(CPPyODEsTest CPPyODEs)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

target_link_libraries(CPPyODEsTest CPPyODEs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
