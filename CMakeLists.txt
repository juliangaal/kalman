cmake_minimum_required(VERSION 3.5)
project(Kalman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++")
set(KALMAN2D_SOURCES
        src/Kalman.cpp
        src/Kalman2d.cpp)

set(KALMAN6D_SOURCES
        src/Kalman.cpp
        src/Kalman6d.cpp)

set(SICK_TEST_SOURCES
        src/Kalman.cpp
        src/SickRobotDayTest.cpp)

set(TEST_SOURCES
        src/Kalman.cpp
        src/Kalman2d.cpp
        src/Kalman6d.cpp
        src/SickRobotDayTest.cpp)

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

add_executable(SickRobotDayTest src/RunSickRobotDayTest.cpp ${SICK_TEST_SOURCES})
target_link_libraries(SickRobotDayTest ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(Test test/test.cpp ${TEST_SOURCES})
target_link_libraries(Test ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
