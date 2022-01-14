cmake_minimum_required(VERSION 2.8)
project(stereo)

# find Pangolin
find_package(Pangolin REQUIRED)

# find OpenCV
set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)

add_executable(stereoVision stereoVision.cpp)
target_link_libraries(stereoVision ${OpenCV_LIBS} ${Pangolin_LIBRARIES})