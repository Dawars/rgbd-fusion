//
// Created by dawars on 2021. 09. 12..
//

#pragma once

class RgbdFusion{
    Eigen::Matrix3f colorInstrinsics, depthIntrinsics;
public:
    RgbdFusion(Eigen::Matrix3f colorIntrinsics, Eigen::Matrix3f depthIntrinsics);

    void refine(cv::Mat rgbImage, cv::Mat depthImage);

    cv::Mat smoothDepth(cv::Mat image);

    cv::Mat calculateNormals(cv::Mat depthImage);
};