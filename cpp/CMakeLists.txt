cmake_minimum_required(VERSION 3.0.0)
project(CPPyODEs VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCE_FILES
    odes.cpp
    vector.cpp
    systems.cpp
    matrix.cpp
    interface.cpp)

set(CMAKE_CXX_STANDARD 20)

#add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_library(CPPyODEs SHARED ${SOURCE_FILES})
#add_executable(CPPyODEsExecutable ${SOURCE_FILES} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
