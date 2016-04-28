#include <ros/ros.h>

#include <chassis_driver/TankDrive.h>
#include <chassis_driver/ArcadeDrive.h>
#include <chassis_driver/TankDriveMessage.h>
#include <chassis_driver/ArcadeDriveMessage.h>

#include <sparkfun_tb6612fng_controller/MotorCommand.h>

namespace sf = sparkfun_tb6612fng_controller;

ros::Subscriber tankDriveSub;
ros::Subscriber arcadeDriveSub;
TankDrive* tankDrive;
ArcadeDrive* arcadeDrive;

void tankDriveCallback(const chassis_driver::TankDriveMessageConstPtr& msg) {
    tankDrive->drive(msg->leftSpeed, msg->rightSpeed);
}

void arcadeDriveCallback(const chassis_driver::ArcadeDriveMessageConstPtr& msg) {
    arcadeDrive->drive(msg->speed, msg->rotation);
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "chassis_drive_controller");
    
    ros::NodeHandle nh;
    
    ros::Publisher frontPub = nh.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/front", 10);
    ros::Publisher backPub = nh.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/back", 10);
    
    tankDrive = new TankDrive(&frontPub, &backPub);
    arcadeDrive = new ArcadeDrive(&frontPub, &backPub);
    
    tankDriveSub = nh.subscribe("tank_drive", 10, tankDriveCallback);
    arcadeDriveSub = nh.subscribe("arcade_drive", 10, arcadeDriveCallback);
    
    ros::spin();
    
    delete tankDrive;
}
