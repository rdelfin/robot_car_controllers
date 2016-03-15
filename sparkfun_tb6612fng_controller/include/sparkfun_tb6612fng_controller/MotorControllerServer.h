#include <ros/ros.h>
#include <sparkfun_tb6612fng_controller/MotorCommand.h>
#include <sparkfun_tb6612fng_controller/DriverInterface.h>

class MotorControllerServer {
public:
    MotorControllerServer(std::string name, int pwmAPin, int dir1APin, int dir2APin, int pwmBPin, int dir1BPin, int dir2BPin, int standbyPin);
    
    void executeCB(const sparkfun_tb6612fng_controller::MotorCommand::ConstPtr &goal);
    
    ~MotorControllerServer();
private:
    ros::NodeHandle nh;
    
    ros::Subscriber subscriber;
    std::string topic_name;
    
    sf_motor::DriverInterface interface;
};