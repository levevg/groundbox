//
// Created by Yauheni Liauchuk on 01.01.22.
//

#ifndef GROUNDBOX_TILEDPLANETSCENE_H
#define GROUNDBOX_TILEDPLANETSCENE_H

#include "Scene.h"

namespace groundbox {

class TilesProvider;

class TiledPlanetScene : public Scene {
public:
    TiledPlanetScene(TilesProvider *tiles_provider, double planet_radius):
            tiles_provider_(tiles_provider), planet_radius_(planet_radius) {}

    [[nodiscard]] cv::Vec4b color_in_direction(cv::Vec3d origin, cv::Vec3d direction, double rad_per_pixel) const override;
private:
    TilesProvider *tiles_provider_;
    double planet_radius_;
};

}

#endif //GROUNDBOX_TILEDPLANETSCENE_H
