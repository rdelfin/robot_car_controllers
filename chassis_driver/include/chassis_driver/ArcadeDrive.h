#pragma once

#include <ros/ros.h>

class ArcadeDrive {

public:
    ArcadeDrive();
    ArcadeDrive(ros::Publisher* frontTopic, ros::Publisher* backTopic);
    
    // Speed goes from -1 to 1. Rotation goes from -1 to 1
    void drive(double speed, double rotation);
    
    ~ArcadeDrive();
private:
    ros::Publisher* frontPub;
    ros::Publisher* backPub;
};
