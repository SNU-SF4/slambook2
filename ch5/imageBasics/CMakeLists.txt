cmake_minimum_required(VERSION 2.8)
project(imageBasics)

# find OpenCV
set(OpenCV_DIR /usr/include/opencv4)
find_package(OpenCV REQUIRED)

add_executable(imageBasics imageBasics.cpp)
target_link_libraries(imageBasics ${OpenCV_LIBS}) # link the exe to opencv's libs

add_executable(undistortImage undistortImage.cpp)
target_link_libraries(undistortImage ${OpenCV_LIBS})
