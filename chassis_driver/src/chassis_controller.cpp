#include <ros/ros.h>

#include <chassis_driver/TankDrive.h>
#include <chassis_driver/TankDriveMessage.h>

ros::Subscriber tankDriveSub;
TankDrive* tankDrive;

void tankDriveCallback(const chassis_driver::TankDriveMessageConstPtr& msg) {
    
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "chassis_drive_controller");
    
    ros::NodeHandle nh;
    
    tankDrive = new TankDrive("sparkfun_tb6612fng_controller/front", "sparkfun_tb6612fng_controller/back");
    
    tankDriveSub = nh.subscribe("tank_drive", 10, tankDriveCallback);
    
    ros::spin();
}