#include <opencv2/opencv.hpp>

#include "groundbox.h"

using groundbox::TilesProvider;
using groundbox::Tile;
using groundbox::Location;
using groundbox::CoordinatesType;
using groundbox::Camera;
using groundbox::TiledPlanetScene;

int main() {

    TilesProvider tiles_provider("/Users/yli/groundbox/tiles/",
        [](const Tile &tile) -> std::string {
            return "http://mt1.google.com/vt/lyrs=s&x=" + std::to_string(tile.x()) +
                   "&y=" + std::to_string(tile.y()) + "&z=" + std::to_string(tile.z());
        });

    TiledPlanetScene earth(&tiles_provider, Location::planet_radius);

    Camera camera(Location(11.64126, 48.12956, 600, CoordinatesType::LonLatAlt),
                  Location(11.64144, 48.12956, 0, CoordinatesType::LonLatAlt),
                  Location(11.64144, 48.2, 1000, CoordinatesType::LonLatAlt),
                  90, 90);

    cv::Mat frame(1024, 1024, CV_8UC4, cv::Scalar(0, 0, 0, 255));

    camera.render(earth, frame, [](const cv::Mat &f, int pixels_done, int total_pixels) {
        if (pixels_done % (20*f.cols) == 1) {
            imshow("F", f);
            cv::waitKey(1);
        }
    });

    cv::waitKey(0);
    return 0;
}
