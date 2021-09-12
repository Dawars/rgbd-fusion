//
// Created by dawars on 2021. 09. 12..
//

#pragma once

class RgbdFusion{
    Eigen::Matrix4f colorInstrinsics, depthIntrinsics;
public:
    RgbdFusion(Eigen::Matrix4f colorIntrinsics, Eigen::Matrix4f depthIntrinsics);

};