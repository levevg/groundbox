//
// Created by Yauheni Liauchuk on 01.01.22.
//

#ifndef GROUNDBOX_SCENE_H
#define GROUNDBOX_SCENE_H

#include <opencv2/opencv.hpp>

namespace groundbox {

class Scene {
public:
    [[nodiscard]] virtual cv::Vec4b color_in_direction(cv::Vec3d origin, cv::Vec3d direction, double rad_per_pixel) const = 0;
};

}

#endif //GROUNDBOX_SCENE_H
