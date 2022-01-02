//
// Created by Yauheni Liauchuk on 01.01.22.
//

#include "TiledPlanetScene.h"
#include "groundbox.h"

namespace groundbox {

cv::Vec4b TiledPlanetScene::color_in_direction(cv::Vec3d origin, cv::Vec3d direction, double rad_per_pixel) const {
    direction = normalize(direction);
    double b = 2 * direction.dot(origin),
           c = origin.dot(origin) - planet_radius_ * planet_radius_,
           d = b * b - 4 * c;
    if (d < 0) return {0, 0, 0, 0};
    double distance = (-b - sqrt(d)) / 2;
    if (distance < 0) return {0, 0, 0, 0};
    cv::Vec3d point = origin + direction * distance;
    Location location(point[0], point[1], point[2], CoordinatesType::XYZ);
    if (location.lat() > 85.0511 || location.lat() < -85.0511) return {255, 255, 255, 0};
    double meters_per_pixel = distance * rad_per_pixel;
    int z = (int)log2(156250.0 / meters_per_pixel);
    if (z < 0) z = 0;
    double x, y;
    auto tile = tiles_provider_->get_tile(location.tile_at_z(z, &x, &y));
    if (tile.empty()) return {0, 0, 255, 255};
    return tile.at<cv::Vec4b>((int)(y * tile.rows), (int)(x * tile.cols));
}

}
