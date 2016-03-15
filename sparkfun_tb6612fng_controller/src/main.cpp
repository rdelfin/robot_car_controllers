#include <ros/ros.h>
#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "sparkfun_tb6612fng_controller");
    
    ros::NodeHandle node;
    
    MotorControllerServer motor1_controller_server("sparkfun_tb6612fng_front_controller/raw", 18, 4, 17, 27);
    
    ros::spin();
    
    return 0;
}