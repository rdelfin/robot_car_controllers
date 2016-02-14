#include <ros/ros.h>

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "raw_motor_controller_node");
    ros::spin();
}