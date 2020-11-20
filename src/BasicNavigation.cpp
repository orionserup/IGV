#include "BasicNavigation.hpp"

MotorController::MotorController(){

    direction = 0;
    speed = 0;

}

void MotorController::ChangeDirection( char dir ){
    
    direction = (direction + dir) % 127;  // update the direction 
    


}

auto MotorController::gettime(){

    return high_resolution_clock::now();

}