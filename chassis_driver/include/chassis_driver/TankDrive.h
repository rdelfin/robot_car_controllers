#pragma once

#include <ros/ros.h>

class TankDrive {

public:
    TankDrive();
    TankDrive(ros::Publisher &frontTopic, ros::Publisher backTopic);
    
    drive(double left, double right);
    
    ~TankDrive();
private:
    ros::Publisher& frontPub;
    ros::Publisher& backPub;
};