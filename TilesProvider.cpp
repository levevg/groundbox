//
// Created by Yauheni Liauchuk on 30.12.21.
//

#include "groundbox.h"

namespace groundbox {

std::string TilesProvider::filename_for_tile_(const Tile &tile) {
    return std::to_string(tile.z()) + "/" +
           std::to_string(tile.x()) + "/" +
           std::to_string(tile.y()) + ".jpg";
}

std::string TilesProvider::path_for_tile_(const Tile &tile) {
    return cache_dir_ + TilesProvider::filename_for_tile_(tile);
}

cv::Mat TilesProvider::get_tile(const Tile &tile) {
    auto cached = get_cached_tile_(tile);
    if (!cached.empty()) return cached;

    if (download_tile_(tile)) {
        return get_cached_tile_(tile);
    } else {
        return {};
    }
}

std::string TilesProvider::url_for_tile_(const Tile &tile) {
    return url_builder_(tile);
}

bool TilesProvider::download_tile_(const Tile &tile) {
    auto path = path_for_tile_(tile);
    auto url = url_for_tile_(tile);
    return utils::download_file(url, path);
}

cv::Mat TilesProvider::get_cached_tile_(const Tile &tile) {
    auto path = path_for_tile_(tile);
    auto memory_cached = get_from_memory_cache(path);
    if (!memory_cached.empty()) {
        return memory_cached;
    }
    auto disk_cached = cv::imread(path, cv::IMREAD_UNCHANGED);
    if (!disk_cached.empty()) {
        cv::Mat converted(disk_cached.rows, disk_cached.cols, CV_8UC4);
        cv::cvtColor(disk_cached, converted, cv::COLOR_BGR2BGRA);
        save_to_memory_cache(path, converted);
        return converted;
    }
    return {};
}

void TilesProvider::save_to_memory_cache(const std::string &key, const cv::Mat &mat) {
    while (memory_cache_.size() >= max_memory_cache_items_) {
        auto oldest = memory_cache_used_keys_.back();
        remove_from_memory_cache(oldest);
    }
    memory_cache_used_keys_.remove(key);
    memory_cache_used_keys_.push_front(key);
    memory_cache_[key] = mat;
}

cv::Mat TilesProvider::get_from_memory_cache(const std::string &key) {
    auto i = memory_cache_.find(key);
    if (i != memory_cache_.end()) {
        return i->second;
    } else {
        return {};
    }
}

void TilesProvider::remove_from_memory_cache(const std::string &key) {
    memory_cache_used_keys_.remove(key);
    memory_cache_.erase(key);
}

}
