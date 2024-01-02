cmake_minimum_required(VERSION 3.0.0)
project(${TEST_PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(LIB_HEADERS "../lib")
include_directories(${LIB_HEADERS})

add_executable(${PROJECT_NAME} main.cpp)

ADD_TEST(AllTests ${PROJECT_NAME})

set(DYLIB_FOLDER "../../build/lib")
target_link_libraries(${PROJECT_NAME} ${LIB_PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${LIB_PROJECT_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
