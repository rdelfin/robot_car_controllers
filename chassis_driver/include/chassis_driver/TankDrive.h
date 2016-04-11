#pragma once

#include <string>
#include <ros/ros.h>

class TankDrive {

public:
    TankDrive();
    TankDrive(std::strinv frontTopic, std::string backTopic);
    ~TankDrive();
    private:
    
};