#pragma once

#include <string>
#include <ros/ros.h>

class TankDrive {

public:
    TankDrive();
    TankDrive(std::string frontTopic, std::string backTopic);
    
    drive(double left, double right);
    
    ~TankDrive();
private:
    ros::Publisher frontPub, backPub;
    ros::NodeHandle nh;
};