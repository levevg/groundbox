//
// Created by Yauheni Liauchuk on 30.12.21.
//

#include <cmath>

#include "groundbox.h"
#include "Location.h"

namespace groundbox {

Tile Location::tile_at_z(int z, double *x_offset, double *y_offset) const {
    double s = pow(2, z);
    double x = (lon_ + 180.0) / 360.0 * (1 << z);
    double y = (1.0 - asinh(tan(lat_ * M_PI / 180.0)) / M_PI) / 2.0 * s;
    if (x_offset) {
        *x_offset = x - floor(x);
    }
    if (y_offset) {
        *y_offset = y - floor(y);
    }
    return {(int)x, (int)y, z};
}

Location::Location(double a, double b, double c, CoordinatesType coordinates_type) {
    switch (coordinates_type) {
        case CoordinatesType::XYZ: {
            x_ = a;
            y_ = b;
            z_ = c;
            lon_ = atan2(b, a) * 180 / M_PI;
            lat_ = atan2(c, sqrt(a * a + b * b)) * 180 / M_PI;
            alt_ = sqrt(a * a + b * b + c * c) - planet_radius;
            break;
        }
        case CoordinatesType::LonLatAlt: {
            lon_ = a;
            lat_ = b;
            alt_ = c;
            c += planet_radius;
            a *= M_PI / 180.0;
            b *= M_PI / 180.0;
            double h = cos(b);
            x_ = c * cos(a) * h;
            y_ = c * sin(a) * h;
            z_ = c * sin(b);
            break;
        }
    }
}

Location Location::elevated_to(double alt) {
    return Location(lon_, lat_, alt, CoordinatesType::LonLatAlt);
}

}
