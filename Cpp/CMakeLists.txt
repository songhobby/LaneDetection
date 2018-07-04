cmake_minimum_required(VERSION 3.10)
project(Cpp)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 11)

add_executable(Cpp main.cpp LaneFilter.cpp LaneFilter.h)

target_link_libraries( Cpp  ${OpenCV_LIBS} )
