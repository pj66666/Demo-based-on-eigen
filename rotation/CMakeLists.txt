project(mrpt_example1)

cmake_minimum_required(VERSION 3.8)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(Eigen3 REQUIRED)


include_directories(${EIGEN3_INCLUDE_DIRS})


# Declare the target (an executable)
add_executable(fixedaxis
fixedaxis.cpp
	)

add_executable(activeaxis
activeaxis.cpp
	)
