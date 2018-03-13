cmake_minimum_required(VERSION 3.9)
project(Kalman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++")
set(KALMAN2D_SOURCES
        src/Kalman.cpp
        src/Kalman2d.cpp)

set(KALMAN6D_SOURCES
        src/Kalman.cpp
        src/Kalman6d.cpp)

find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

include_directories(include)
include_directories(${xtensor_INCLUDE_DIRS} ${xtensor_blas_INCLUDE_DIRS})

add_executable(Kalman2d src/Run2d.cpp ${KALMAN2D_SOURCES})
target_link_libraries(Kalman2d ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(Kalman6d src/Run6d.cpp ${KALMAN6D_SOURCES})
target_link_libraries(Kalman6d ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(Test test/test.cpp ${KALMAN6D_SOURCES} ${KALMAN2D_SOURCES})
target_link_libraries(Test ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})