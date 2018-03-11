cmake_minimum_required(VERSION 3.9)
project(Kalman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++")
set(KALMAN_SOURCES
        src/Kalman2d.cpp
        src/Kalman.cpp)

find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

include_directories(include)
include_directories(${xtensor_INCLUDE_DIRS} ${xtensor_blas_INCLUDE_DIRS})

add_executable(Kalman2d src/Main.cpp ${KALMAN_SOURCES})
target_link_libraries(Kalman2d ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})