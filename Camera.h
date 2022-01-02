//
// Created by Yauheni Liauchuk on 01.01.22.
//

#ifndef GROUNDBOX_CAMERA_H
#define GROUNDBOX_CAMERA_H

#include <opencv2/opencv.hpp>

#include "Location.h"

namespace groundbox {

class Scene;

class Camera {
public:
    Camera(const Location &origin, const Location &target, const Location &up, double h_fov, double v_fov);

    [[nodiscard]] Location origin() const { return origin_; }
    [[nodiscard]] Location target() const { return target_; }
    [[nodiscard]] cv::Vec3d direction() const { return direction_; }
    [[nodiscard]] cv::Vec3d up_axis() const { return up_axis_; }
    [[nodiscard]] cv::Vec3d right_axis() const { return right_axis_; }
    [[nodiscard]] double h_fov() const { return h_fov_; }
    [[nodiscard]] double v_fov() const { return v_fov_; }

    void render(const Scene &scene, cv::Mat &out, const std::function<void(const cv::Mat &, int, int)> &progress_callback);

private:
    Location origin_;
    Location target_;
    cv::Vec3d direction_;
    cv::Vec3d up_axis_;
    cv::Vec3d right_axis_;
    double h_fov_;
    double v_fov_;
};

}


#endif //GROUNDBOX_CAMERA_H
