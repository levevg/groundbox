//
// Created by Yauheni Liauchuk on 30.12.21.
//

#ifndef GROUNDBOX_LOCATION_H
#define GROUNDBOX_LOCATION_H

#include <opencv2/opencv.hpp>

namespace groundbox {

class Tile;

enum class CoordinatesType {
    XYZ, LonLatAlt
};

class Location {
public:
    Location(double a, double b, double c, CoordinatesType coordinates_type);
    Location(double lon, double lat): Location(lon, lat, 0, CoordinatesType::LonLatAlt) {}

    Location elevated_to(double alt);

    [[nodiscard]] double lon() const { return lon_; }
    [[nodiscard]] double lat() const { return lat_; }
    [[nodiscard]] double alt() const { return alt_; }
    [[nodiscard]] double x() const { return x_; }
    [[nodiscard]] double y() const { return y_; }
    [[nodiscard]] double z() const { return z_; }
    [[nodiscard]] cv::Vec3d xyz() const { return {x_, y_, z_}; }
    [[nodiscard]] Tile tile_at_z(int z, double *x_offset = nullptr, double *y_offset = nullptr) const;

    constexpr static const double planet_radius = 6371008.8;

private:
    double lon_;
    double lat_;
    double alt_;
    double x_;
    double y_;
    double z_;
};

}

#endif //GROUNDBOX_LOCATION_H
