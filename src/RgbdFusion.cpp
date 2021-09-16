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

cv::Mat RgbdFusion::calculateNormals(cv::Mat depth) {

    cv::Mat normals(depth.size(), CV_32FC3);

    for(int y = 0; y < depth.rows; ++y) {
        for(int x = 0; x < depth.cols; ++x) {
            double dzdy = (depth.at<float>(std::min(depth.rows, y + 1), x) - depth.at<float>(std::max(0, y - 1), x)) / 2.0;
            double dzdx = (depth.at<float>(y, std::min(depth.cols, x + 1)) - depth.at<float>(y, std::max(depth.cols, x - 1))) / 2.0;

            cv::Vec3d d(dzdx, dzdy, -1.0f);
            cv::Vec3d n = normalize(d);

            normals.at<cv::Vec3f>(y, x) = n;
        }
    }

    cv::Mat normalDisp;
    normals.convertTo(normalDisp, CV_8UC3, 127, 127);
    cv::cvtColor(normalDisp, normalDisp, cv::COLOR_BGR2RGB);
    std::cout << normalDisp << std::endl;

    cv::imwrite("normal.png", normalDisp);

    return normals;
}
