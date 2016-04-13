#pragma once

#include <ros/ros.h>

class TankDrive {

public:
    TankDrive();
    TankDrive(ros::Publisher* frontTopic, ros::Publisher* backTopic);
    
    void drive(double left, double right);
    
    ~TankDrive();
private:
    ros::Publisher* frontPub;
    ros::Publisher* backPub;
};