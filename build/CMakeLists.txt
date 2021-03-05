cmake_minimum_required(VERSION 3.10)  #require a minimum level of CMAKE

project(IGV LANGUAGES CXX VERSION 1.1)  # this project is called IGV and Version 1.1

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -pthread") # all errors on
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG") # have a debug option
set(CMAKE_CXX_FLAGS_RELEASE "-Oz") # have an optimized version for the release

set(GPIOLIB /usr/local/lib/libJetsonGPIO.a)
set(SERIALLIB /usr/local/lib/libCppLinuxSerial.a)
set(GPSLIB /usr/local/lib/libTinyGPS++.a)

file(GLOB SOURCES "../src/*.cpp" "../test/*.cpp")  # use all of the sources in /src and /test

find_package(OpenCV REQUIRED)  # use opencv for this project

include(GNUInstallDirs)

include_directories(../include /usr/local/include)  #include the correct header files from opencv and local headers
include_directories(${OpenCV_INCLUDE_DIRS}) #include the opencv headers
include_directories(../test) #include the tests

set(EXECUTABLE_OUTPUT_PATH ../bin) # put the executable in /bin
set(LIBRARY_OUTPUT_PATH ../lib)

add_executable(${PROJECT_NAME} ${SOURCES})  # make an executable taking all of the sources 

add_library(IGVComplete INTERFACE )

target_link_libraries(IGVComplete INTERFACE ${GPIOLIB})
target_link_libraries(IGVComplete INTERFACE ${GPSLIB} )
target_link_libraries(IGVComplete INTERFACE ${SERIALLIB})  # make sure the libs are included
target_link_libraries(IGVComplete INTERFACE ${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME} IGVComplete)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
install(TARGETS IGVComplete LIBRARY DESTINATION /usr/local/lib
        PUBLIC_HEADER DESTINATION /usr/local/include)




