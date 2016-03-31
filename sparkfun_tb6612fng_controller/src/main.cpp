#include <ros/ros.h>
#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>
#include <wiringPi.h>

int main(int argc, char *argv[]) {
    ros::init(argc, argv, "sparkfun_tb6612fng_controller");
    
    ros::NodeHandle node;
    
    wiringPiSetupGpio();
    
    MotorControllerServer motor1_controller_server("sparkfun_tb6612fng_controller/front", 17, 22, 23, 10, 9, 11, 27);
    MotorControllerServer motor2_controller_server("sparkfun_tb6612fng_controller/back", 4, 18, 24, 25, 12, 16, 20);
    
    ros::spin();
    
    return 0;
}