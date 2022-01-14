cmake_minimum_required(VERSION 2.8)
project(rgbd)

# find OpenCV
set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)

add_executable(joinMap joinMap.cpp)
target_link_libraries(joinMap ${OpenCV_LIBS} ${Pangolin_LIBRARIES})