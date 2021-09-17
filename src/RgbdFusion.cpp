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
//    depthImage = this->bilateralSmoothing(depthImage);
    depthImage = this->gaussianSmoothing(depthImage);
    cv::Mat normals = this->calculateNormals(depthImage);

}

cv::Mat RgbdFusion::gaussianSmoothing(cv::Mat image) {
    cv::Mat out;
    cv::GaussianBlur(image, out, cv::Size{5,5}, 0.1);
    return out;
}

cv::Mat RgbdFusion::bilateralSmoothing(cv::Mat image) {
    cv::Mat smoothDepth;

    float diag = std::sqrt(image.rows * image.rows + image.cols * image.cols);
    float sigmaSpace = 3; // proportional to diagonal
    float sigmaColor = 2; // proportional to mean/median of image gradients
    cv::bilateralFilter(image, smoothDepth, 5, sigmaColor, sigmaSpace);

    // for display in PNG
    smoothDepth.convertTo(smoothDepth, CV_16UC1);
    std::cout << smoothDepth << std::endl;
    cv::imwrite("bilateral.png", smoothDepth);

    return smoothDepth;
}

cv::Mat RgbdFusion::calculateNormals(cv::Mat depth) {

    cv::Mat normals(depth.size(), CV_32FC3);
    cv::Mat zx;
    cv::Mat zy;
    bool centralDiff = false;
    if (!centralDiff) {
        cv::Sobel(depth, zx, -1, 1, 0);
        cv::Sobel(depth, zy, -1, 0, 1);
    }
    for (int y = 0; y < depth.rows; ++y) {
        for (int x = 0; x < depth.cols; ++x) {
            // central differnces
            double dzdy, dzdx;
            if (centralDiff) {
                dzdy = (depth.at<float>(std::min(depth.rows, y + 1), x) - depth.at<float>(std::max(0, y - 1), x)) / 2.0;
                dzdx = (depth.at<float>(y, std::min(depth.cols, x + 1)) - depth.at<float>(y, std::max(depth.cols, x - 1))) / 2.0;
            } else {
                dzdx = zx.at<float>(y, x);
                dzdy = zy.at<float>(y, x);
            }

            cv::Vec3d d(dzdx, dzdy, -1.0f);
            cv::Vec3d n = normalize(d);

            normals.at<cv::Vec3f>(y, x) = n;
        }
    }

//    cv::Mat normalDisp; // for display only
//    normals.convertTo(normalDisp, CV_8UC3, 127, 127);
//    cv::cvtColor(normalDisp, normalDisp, cv::COLOR_BGR2RGB);
//    std::cout << normalDisp << std::endl;
//    cv::imwrite("normal.png", normalDisp);

    return normals;
}
