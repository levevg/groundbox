//
// Created by Yauheni Liauchuk on 30.12.21.
//

#include <cmath>

#include "groundbox.h"

namespace groundbox {

Location Tile::top_left_location() const {
    return Tile::location_(x_, y_, z_);
}

Location Tile::bottom_left_location() const {
    return Tile::location_(x_, y_ + 1, z_);
}

Location Tile::top_right_location() const {
    return Tile::location_(x_ + 1, y_, z_);
}

Location Tile::bottom_right_location() const {
    return Tile::location_(x_ + 1, y_ + 1, z_);
}

Location Tile::center_location() const {
    return Tile::location_(x_ + 0.5, y_ + 0.5, z_);
}

Location Tile::location_(double x, double y, double z) {
    double s = pow(2, z);
    double lon = x / s * 360 - 180;
    double n = M_PI - 2.0 * M_PI * y / s;
    double lat = 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
    return { lon, lat, 0, CoordinatesType::LonLatAlt };
}

Tile Tile::top_left_child() const {
    return {x_ * 2, y_ * 2, z_ + 1};
}

Tile Tile::bottom_left_child() const {
    return {x_ * 2, y_ * 2 + 1, z_ + 1};
}

Tile Tile::top_right_child() const {
    return {x_ * 2 + 1, y_ * 2, z_ + 1};
}

Tile Tile::bottom_right_child() const {
    return {x_ * 2 + 1, y_ * 2 + 1, z_ + 1};
}

Tile Tile::parent_tile() const {
    return {x_ / 2, y_ / 2, z_ - 1};
}

}
