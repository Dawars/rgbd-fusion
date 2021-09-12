//
// Created by Komorowicz David on 2020. 06. 15..
//
#include <iostream>

#include "eigen3/Eigen/Core"

#include "rgbd_fusion/RgbdFusion.h"


constexpr int DATASET_LION = 0;
constexpr int DATASET_HIEROGLYPH = 1;
constexpr int DATASET_FREIBURG = 2;

int main(){
    Eigen::Matrix4f colorIntrinsics;
    Eigen::Matrix4f depthIntrinsics;

    int dataset = DATASET_LION;


    switch (dataset) {
        // https://vision.in.tum.de/data/datasets/rgbd-dataset/download
        case DATASET_FREIBURG:
            colorIntrinsics << 525.0f, 0.0f, 319.5f,
                    0.0f, 525.0f, 239.5f,
                    0.0f, 0.0f, 1.0f;
            depthIntrinsics = colorIntrinsics;
            break;
            // https://vision.in.tum.de/data/datasets/intrinsic3d
        case DATASET_HIEROGLYPH:
        case DATASET_LION:
            colorIntrinsics << 1170.19, 0, 647.75, 0,
                    0, 1170.19, 483.75, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;
            depthIntrinsics << 577.871, 0, 319.623, 0,
                    0, 580.258, 239.624, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;
            break;
    }


    RgbdFusion rgbd(colorIntrinsics, depthIntrinsics);

    return 0;
}