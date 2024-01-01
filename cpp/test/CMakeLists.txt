cmake_minimum_required(VERSION 3.0.0)
project(CPPyODEs VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(LIB_HEADERS "../lib")
include_directories(${LIB_HEADERS})

set(CMAKE_CXX_STANDARD 20)

add_executable(CPPyODEsTest main.cpp)

set(DYLIB_FOLDER "../../build/lib")
target_link_libraries(CPPyODEsTest CPPyODEs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
