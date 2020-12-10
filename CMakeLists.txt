cmake_minimum_required(VERSION 3.10)  #require a minimum level of CMAKE

project(IGV VERSION 1.0)  # this project is called IGV and Version 1.0

set(CMAKE_CXX_STANDARD 17)   # use c++ 17
set(CMAKE_GXX_FLAGS "-Wall -Wextra -Wconversion  -pedantic -std=c++17") # all errors on

file(GLOB SOURCES "./src/*.cpp" "./test/*.cpp")  # use all of the sources in /src and /test

find_package(OpenCV REQUIRED)  # use opencv for this project

include_directories(./include)  #include the correct header files from opencv and local headers
include_directories(${OpenCV_INCLUDE_DIRS}) #include the opencv headers

set(EXECUTABLE_OUTPUT_PATH ../bin) # put the executable in /bin
set(LIBRARY_OUTPUT_PATH ../lib)  # put the libraries in /lib

add_library(IGVstatic ${SOURCES})

add_executable(IGV.exe ${SOURCES})  # make an executable taking all of the sources 

target_link_libraries(IGV.exe ${OpenCV_LIBS} IGVstatic )  # make sure the opencv libs are included



