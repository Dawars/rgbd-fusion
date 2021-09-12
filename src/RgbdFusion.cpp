//
// Created by dawars on 2021. 09. 12..
//

#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include "rgbd_fusion/RgbdFusion.h"

RgbdFusion::RgbdFusion(Eigen::Matrix3f colorIntrinsics, Eigen::Matrix3f depthIntrinsics) :
        colorInstrinsics(colorIntrinsics), depthIntrinsics(depthIntrinsics) {
}

void RgbdFusion::refine(cv::Mat rgbImage, cv::Mat depthImage) {
    auto originalDepth = depthImage.clone();
    cv::Mat smoothDepth = this->smoothDepth(depthImage);
    cv::Mat normals = this->calculateNormals(smoothDepth);

}

cv::Mat RgbdFusion::smoothDepth(cv::Mat image) {
    cv::Mat smoothDepth;

    float diag = std::sqrt(image.rows * image.rows + image.cols * image.cols);
    float sigmaSpace = 0.1 * diag; // proportional to diagonal
    float sigmaColor = 0.1; // proportional to mean/median of image gradients
    cv::bilateralFilter(image, smoothDepth, 15, sigmaColor, sigmaSpace);

    cv::imwrite("bilateral.png", smoothDepth);

    return smoothDepth;
}

cv::Mat RgbdFusion::calculateNormals(cv::Mat depthImage) {
    cv::Mat zx;
    cv::Mat zy;
    cv::Sobel(depthImage, zx, -1, 1, 0);
    cv::Sobel(depthImage, zy, -1, 0, 1);

    cv::imwrite("zx.png", zx);
    cv::imwrite("zy.png", zy);

    // todo handedness
    std::vector<cv::Mat> channels {cv::Mat(depthImage.rows, depthImage.cols, zx.type(), 1), zy, zx}; // todo BGR
    cv::Mat normal;
    cv::merge(channels, normal);
    cv::imwrite("normal.png", normal);
    cv::Mat denom;
    cv::sqrt(normal, denom); // fixme this is not what we want
    normal = normal / denom;

    return normal;
}
