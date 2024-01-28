cmake_minimum_required(VERSION 3.10)
project(NullSpaceTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(Eigen3 REQUIRED)

include_directories(
        ${EIGEN3_INCLUDE_DIR}
)

add_executable(NullSpaceTest hessian_nullspace_test.cpp)

