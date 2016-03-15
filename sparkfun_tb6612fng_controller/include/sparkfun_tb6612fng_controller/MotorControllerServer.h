#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <sparkfun_tb6612fng_controller/MotorCommandAction.h>
#include <sparkfun_tb6612fng_controller/DriverInterface.h>

class MotorControllerServer {
public:
    MotorControllerServer(std::string name, int pwmPin, int dir1Pin, int dir2Pin, int standbyPin);
    
    void executeCB(const sparkfun_tb6612fng_controller::MotorCommandGoalConstPtr &goal);
    
    ~MotorControllerServer();
private:
    ros::NodeHandle nh;
    
    actionlib::SimpleActionServer<sparkfun_tb6612fng_controller::MotorCommandAction> server;
    std::string action_name;
    
    sparkfun_tb6612fng_controller::MotorCommandResult result;
    sparkfun_tb6612fng_controller::MotorCommandFeedback feedback;
    
    sf_motor::DriverInterface interface;
};