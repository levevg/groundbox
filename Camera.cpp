//
// Created by Yauheni Liauchuk on 01.01.22.
//

#include "Camera.h"
#include "groundbox.h"

namespace groundbox {

Camera::Camera(const Location &origin, const Location &target, const Location &up, double h_fov, double v_fov):
        origin_(origin), target_(target), h_fov_(h_fov), v_fov_(v_fov)
{
    direction_ = normalize(target.xyz() - origin.xyz());
    auto u = normalize(up.xyz() - target.xyz());
    right_axis_ = direction_.cross(u);
    up_axis_ = right_axis_.cross(direction_);
    right_axis_ *= tan(h_fov / 360 * M_PI);
    up_axis_ *= tan(v_fov / 360 * M_PI);
}

void Camera::render(const Scene &scene, cv::Mat &out, const std::function<void(const cv::Mat &, int, int)> &progress_callback) {
    double rad_per_pixel = fmin(h_fov_ / out.cols, v_fov_ / out.rows) / 180 * M_PI;
    int total_pixels = out.rows * out.cols;
    int pixels_done = 0;
    for (int y = 0; y < out.rows; ++y) {
        for (int x = 0; x < out.cols; ++x) {
            auto d = direction_ + ((double)(x + 0.5) / out.cols - 0.5) * 2 * right_axis_ + (0.5 - (double)(y + 0.5) / out.rows) * 2 * up_axis_;
            auto src = scene.color_in_direction(origin().xyz(), d, rad_per_pixel);
            auto dst = out.at<cv::Vec4b>(y, x);
            int a = src[3], b = 255 - a;
            out.at<cv::Vec4b>(y, x) = cv::Vec4b((a * src[0] + b * dst[0]) / 255, (a * src[1] + b * dst[1]) / 255, (a * src[2] + b * dst[2]) / 255, 255);
            ++pixels_done;
            progress_callback(out, pixels_done, total_pixels);
        }
    }
}

}
