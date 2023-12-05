cmake_minimum_required(VERSION 3.23)
project(Spottingfy)
set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
add_executable(Spottingfy main.cpp song.cpp)
target_link_libraries(Spottingfy PRIVATE ${CURL_LIBRARIES})