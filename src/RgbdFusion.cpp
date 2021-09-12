//
// Created by dawars on 2021. 09. 12..
//

#include <Eigen/Core>
#include "rgbd_fusion/RgbdFusion.h"

RgbdFusion::RgbdFusion(Eigen::Matrix4f colorIntrinsics, Eigen::Matrix4f depthIntrinsics) :
        colorInstrinsics(colorIntrinsics), depthIntrinsics(depthIntrinsics) {
}
