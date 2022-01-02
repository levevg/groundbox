//
// Created by Yauheni Liauchuk on 30.12.21.
//

#ifndef GROUNDBOX_TILESPROVIDER_H
#define GROUNDBOX_TILESPROVIDER_H

#include <string>
#include <map>
#include <opencv2/opencv.hpp>

namespace groundbox {

class Tile;

class TilesProvider {
public:
    TilesProvider(std::string &&cache_dir, std::function<std::string(const Tile &tile)> &&url_builder, int max_memory_cache_items = 100):
        cache_dir_(std::move(cache_dir)), url_builder_(std::move(url_builder)), max_memory_cache_items_(max_memory_cache_items) {}
    cv::Mat get_tile(const Tile &tile);

private:
    std::string cache_dir_;
    std::function<std::string(const Tile &tile)> url_builder_;
    std::map<std::string, cv::Mat> memory_cache_;
    std::list<std::string> memory_cache_used_keys_;
    int max_memory_cache_items_;

    static std::string filename_for_tile_(const Tile &tile);
    std::string path_for_tile_(const Tile &tile);
    std::string url_for_tile_(const Tile &tile);
    bool download_tile_(const Tile &tile);
    cv::Mat get_cached_tile_(const Tile &tile);
    void save_to_memory_cache(const std::string &key, const cv::Mat &mat);
    cv::Mat get_from_memory_cache(const std::string &key);
    void remove_from_memory_cache(const std::string &key);
};

}

#endif //GROUNDBOX_TILESPROVIDER_H
