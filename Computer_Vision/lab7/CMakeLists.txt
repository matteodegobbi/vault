cmake_minimum_required(VERSION 2.8)                            
project(panoramic)                                         

find_package( OpenCV REQUIRED )                              
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(panoramic main.cpp ImageStitcher.cpp panoramic_utils.cpp)                         
target_link_libraries(panoramic ${OpenCV_LIBS})   
