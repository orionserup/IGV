#IGV Winter 2021
#Author: ORION SERUP

#---------------------------- PROJECT CONFIGURATION -----------------------------------#
#======================================================================================#

cmake_minimum_required(VERSION 3.10)  #require a minimum level of CMAKE

project(IGV LANGUAGES CXX VERSION 1.2)  # this project is called IGV and Version 1.1

#======================================================================================#

#--------------------------- COMPILE CONFIGURATION ------------------------------------# 
#======================================================================================#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread -DPHIDGET") # all errors on and treat it like a dll but an executable
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -DDEBUG") # have a debug option
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -march=native") # have an optimized version for the release

#========================================================================================#

#----------------------------- EXTERNAL LIBRARIES ----------------------------------------#
#=========================================================================================#

set(GPIOLIB /usr/local/lib/libJetsonGPIO.a)
set(SERIALLIB /usr/local/lib/libCppLinuxSerial.a)
set(GPSLIB /usr/local/lib/libTinyGPS++.a)
set(LIDARLIB /usr/local/lib/libydlidar_driver.so)
set(PILOTLIB /usr/local/lib/IGVPilot.a)
set(MOTORLIB /usr/lib/libphidget22.so)
set(DRIVERLIB /usr/local/lib/IGVDriver.a)
set(PHIDGETLIB /usr/lib/libphidget22.so)

set(LIBRARIES ${SERIALLIB} ${GPSLIB} ${LIDARLIB} ${PHIDGETLIB})

#==========================================================================================#

#------------------------------------ SOURCES ----------------------------------------------#
#===========================================================================================#

file(GLOB SOURCES ../src/*.cpp ../test/test.cpp)  # use all of the sources in /src and /test
file(GLOB INCLUDES ../include/*.hpp)

#===========================================================================================#

#--------------------------------- TESTS ---------------------------------------------------#
#===========================================================================================#



#===========================================================================================#

#------------------------------- EXTERNAL PACKAGES -----------------------------------------#
#===========================================================================================#

find_package(OpenCV REQUIRED)  # use opencv for this project

#===========================================================================================#

#----------------------------- INCLUDE DIRECTORIES -----------------------------------------#
#===========================================================================================#

include_directories(../include /usr/local/include)  #include the correct header files from opencv and local headers
include_directories(${OpenCV_INCLUDE_DIRS}) #include the opencv headers
include_directories(../test) #include the tests

#============================================================================================#

#------------------------------------ OUTPUT PATH -------------------------------------------#
#============================================================================================#

set(EXECUTABLE_OUTPUT_PATH ../bin) # put the executable in /bin
set(LIBRARY_OUTPUT_PATH ../lib) # put the libraries in /lib

#============================================================================================#

#----------------------------- BUILD TARGET CONFIGURATION ------------------------------------#
#=============================================================================================#

add_executable(${PROJECT_NAME} ${SOURCES})  # make an executable taking all of the sources 
#add_executable(libIGV.so ${SOURCES}) # library 

#set_target_properties(libIGV.so PROPERTIES COMPILE_FLAGS "-fPIC -pie") # flags for a pseudo executeable
#set_target_properties(libIGV.so PROPERTIES LINKER_FLAGS "-Wl,-E") # flags for creating a shared library
#set_target_properties(libIGV.so PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../lib) # have it put into the lib folder

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ../include/IGV.hpp) # set the header for the project

#==============================================================================================#

#---------------------------------------- LINKAGE ---------------------------------------------#
#==============================================================================================#

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${LIBRARIES}) # link all of the libs
#target_link_libraries(libIGV.so ${OpenCV_LIBS} ${LIBRARIES})

#=============================================================================================#

#-------------------------------------- INSTALLATION -----------------------------------------# 
#=============================================================================================#

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

install(FILES ${INCLUDES} DESTINATION /usr/local/include) # install the files in the right location

#install(TARGETS libIGV.so DESTINATION /usr/local/lib) #install the library

#==============================================================================================#



