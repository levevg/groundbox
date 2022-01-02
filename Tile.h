//
// Created by Yauheni Liauchuk on 30.12.21.
//

#ifndef GROUNDBOX_TILE_H
#define GROUNDBOX_TILE_H

namespace groundbox {

class Location;

class Tile {
public:
    Tile(int x, int y, int z) : x_(x), y_(y), z_(z) {}

    [[nodiscard]] int x() const { return x_; }
    [[nodiscard]] int y() const { return y_; }
    [[nodiscard]] int z() const { return z_; }

    [[nodiscard]] Location top_left_location() const;
    [[nodiscard]] Location bottom_left_location() const;
    [[nodiscard]] Location top_right_location() const;
    [[nodiscard]] Location bottom_right_location() const;
    [[nodiscard]] Location center_location() const;

    [[nodiscard]] Tile top_left_child() const;
    [[nodiscard]] Tile bottom_left_child() const;
    [[nodiscard]] Tile top_right_child() const;
    [[nodiscard]]  Tile bottom_right_child() const;
    [[nodiscard]] Tile parent_tile() const;

private:
    int x_, y_, z_;

    static Location location_(double x, double y, double z);
};

}

#endif //GROUNDBOX_TILE_H
