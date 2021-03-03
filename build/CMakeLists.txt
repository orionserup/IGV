cmake_minimum_required(VERSION 3.10)  #require a minimum level of CMAKE

project(IGV VERSION 1.1)  # this project is called IGV and Version 1.1

SET(CMAKE_CXX_COMPILER /usr/bin/clang++) # set the compiler to be clang for the speed

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -pthread") # all errors on
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG") # have a debug option
set(CMAKE_CXX_FLAGS_RELEASE "-Oz") # have an optimized version for the release

set(BUILD_SHARED_LIBS ON)

file(GLOB SOURCES "../src/*.cpp" "../test/*.cpp")  # use all of the sources in /src and /test

find_package(OpenCV REQUIRED)  # use opencv for this project

include(GNUInstallDirs)

include_directories(../include /usr/local/include)  #include the correct header files from opencv and local headers
include_directories(${OpenCV_INCLUDE_DIRS}) #include the opencv headers
include_directories(../test) #include the tests

set(EXECUTABLE_OUTPUT_PATH ../bin) # put the executable in /bin
set(LIBRARY_OUTPUT_PATH ../lib)

add_executable(${PROJECT_NAME} ../src/main.cpp)  # make an executable taking all of the sources 
add_library(IGVlib SHARED ${SOURCES})

set_target_properties(IGVlib PROPERTIES PUBLIC_HEADER ../include/IGV.hpp)
target_include_directories(IGVlib PRIVATE ../include)
target_include_directories(IGVlib PRIVATE ../src)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})  # make sure the opencv libs are included
target_link_libraries(${PROJECT_NAME} IGVlib)
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libCppLinuxSerial.a)  # include the serial functionality
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libJetsonGPIO.a)   # include the gpio functionality
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libTinyGPS++.a)   # include the gps functionality

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
install(TARGETS IGVlib 
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})




