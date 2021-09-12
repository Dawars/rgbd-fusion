cmake_minimum_required(VERSION 3.12...3.16)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${rgbd_fusion_SOURCE_DIR}/include/rgbd_fusion/*.h")

add_library(rgbd_fusion ${HEADER_LIST} RgbdFusion.cpp
        )
target_compile_features(rgbd_fusion PRIVATE cxx_std_17)

target_include_directories(rgbd_fusion PUBLIC ../include)

target_include_directories(rgbd_fusion PRIVATE Eigen3::Eigen)

target_link_libraries(rgbd_fusion PRIVATE fmt::fmt)

if(OpenMP_CXX_FOUND)
    target_link_libraries(rgbd_fusion PRIVATE OpenMP::OpenMP_CXX)
endif()

#target_link_libraries(rgbd_fusion PUBLIC Ceres::ceres)
target_link_libraries(rgbd_fusion PRIVATE Eigen3::Eigen)
#target_link_libraries(rgbd_fusion PRIVATE sophus)
target_link_libraries(rgbd_fusion PUBLIC opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)
#target_link_libraries(rgbd_fusion PRIVATE "${TORCH_LIBRARIES}")