cmake_minimum_required(VERSION 3.12...3.16)
project(RGBD-Fusion VERSION 0.1 LANGUAGES CXX)

find_package(OpenMP)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

add_subdirectory(libs/fmt)
#add_subdirectory(libs/Sophus)
#add_subdirectory(libs/ceres-solver)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)

