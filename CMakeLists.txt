cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
project(GroundBox)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GroundBox main.cpp Utils.cpp Utils.h TilesProvider.cpp TilesProvider.h Tile.cpp Tile.h Location.cpp Location.h groundbox.h Camera.cpp Camera.h Scene.cpp Scene.h TiledPlanetScene.cpp TiledPlanetScene.h)

target_link_libraries(GroundBox ${OpenCV_LIBS})