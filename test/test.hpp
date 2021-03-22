
#include "IGV.hpp"
#include <iostream>
#include <fstream>

namespace igv{

/**
 * @class Test
 * @brief  Test Class
 */
class Test{

public:

    /**
     * @fn Test
     * @brief  Constructs Test Object
     * @param  logfile: File to print logs to 
     */
    Test(const char* logfile);

    /**
     * @fn Test
     * @brief  Constructs Test Object without a log file
     */
    Test() = default;

    /**
     * @fn ~Test
     * @brief  Destructs Test Object
     */
    ~Test();

    /**
     * @fn OpenLogFile
     * @brief  Opens a Logfile to write into
     * @param  logfile: Name of logfile to open
     * @returns bool: If the Log File was opened
     */
    bool OpenLogFile(const char* logfile);

    /**
     * @fn Ready
     * @brief Checks if the Test is ready to be run
     * @returns bool: If the Test Class if Ready
     */
    bool Ready();

    bool RunAllTests();

    /**
     * @test Camera Test
     * @brief  Tests to see if the Cameras are connected and get valid images
     * @retval bool: If the Test is passed
     */
    bool CameraTest();

    /**
     * @test Motor Test
     * @brief  Tests all of the Motor Functionality
     * @retval bool: If the Test was passed
     */
    bool MotorTest();

    /**
     * @test LIDAR Test
     * @brief   Tests LIDAR Functionality
     * @retval  bool: If the Test was passed
     */
    bool LIDARTest();
    
    /**
     * @test GPS Test
     * @brief  Tests all of the GPS Functionality 
     * @retval bool: If the Test was Passed
     */
    bool GPSTest();

    /**
     * @test Lane Detection Test
     * @brief   Tests all of the Lane Detection Functionality
     * @param  filename: Image file name to open
     * @retval bool: Returns if the Test was passed
     */
    bool LaneDetectionTest(string filename);

    /**
     * @test Object Detection Test
     * @brief  Tests all of the Lane Detection Functionality
     * @retval bool: If the Test was passed
     */
    bool ObjectDetectionTest();

    /**
     * @test Sensors Test
     * @brief  Tests all of the Sensors and Their Functionality
     * @retval bool: If the Test was passed
     */
    bool SensorsTest();

private:

    ofstream logfile; ///< ostream object for the log file 

};

}