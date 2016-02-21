#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <sparkfun_tb6612fng_controller/MotorCommandAction.h>

class MotorControllerServer {
public:
    MotorControllerServer(std::string name);
    
    void executeCB(const sparkfun_tb6612fng_controller::MotorCommandGoalConstPtr &goal);
    
    ~MotorControllerServer();
private:
    ros::NodeHandle nh;
    
    actionlib::SimpleActionServer<sparkfun_tb6612fng_controller::MotorCommandAction> server;
    std::string action_name;
    
    sparkfun_tb6612fng_controller::MotorCommandResult result;
    sparkfun_tb6612fng_controller::MotorCommandFeedback feedback;
};