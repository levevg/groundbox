//
// Created by Yauheni Liauchuk on 30.12.21.
//

#include <iostream>

#include "Utils.h"

namespace groundbox::utils {

bool download_file(const std::string &url, const std::string &filename) {
    char command[1000];
    sprintf(command, R"(curl -s --create-dirs -o "%s" "%s")", filename.c_str(), url.c_str());
    return system(command) == 0;
}

}
