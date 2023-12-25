cmake_minimum_required(VERSION 2.8)

project(test_eigen)


find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(test_eigen_map test_eigen_map.cpp)

