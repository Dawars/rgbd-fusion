//
// Created by Komorowicz David on 2020. 06. 15..
//
#include <iostream>

#include "eigen3/Eigen/Core"
#include <opencv2/opencv.hpp>

#include "rgbd_fusion/RgbdFusion.h"


constexpr int DATASET_LION = 0;
constexpr int DATASET_HIEROGLYPH = 1;
constexpr int DATASET_FREIBURG = 2;

int main(){
    Eigen::Matrix3f colorIntrinsics;
    Eigen::Matrix3f depthIntrinsics;

    std::string colorPath;
    std::string depthPath;

    int dataset = DATASET_FREIBURG;


    switch (dataset) {
        // https://vision.in.tum.de/data/datasets/rgbd-dataset/download
        case DATASET_FREIBURG:
            colorIntrinsics << 525.0f, 0.0f, 319.5f,
                    0.0f, 525.0f, 239.5f,
                    0.0f, 0.0f, 1.0f;
            depthIntrinsics = colorIntrinsics;
            colorPath = "../../datasets/rgbd_dataset_freiburg1_xyz/rgb/1305031102.175304.png";
            depthPath = "../../datasets/rgbd_dataset_freiburg1_xyz/depth/1305031102.160407.png";
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

    auto rgbImage = cv::imread(colorPath);
    auto depthImage = cv::imread(depthPath,cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
    depthImage.convertTo(depthImage, CV_32FC1); // or CV_32F works (too)

    rgbd.refine(rgbImage, depthImage);

    return 0;
}