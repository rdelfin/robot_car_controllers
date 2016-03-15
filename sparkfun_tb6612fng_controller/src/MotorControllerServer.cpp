#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>

MotorControllerServer::MotorControllerServer(std::string name, int pwmAPin, int dir1APin, int dir2APin, int pwmBPin, int dir1BPin, int dir2BPin, int standbyPin)
    : topic_name(name),
      interface(pwmAPin, dir1APin, dir2APin, pwmBPin, dir1BPin, dir2BPin, standbyPin)
{
    subscriber = nh.subscribe(name, 100, &MotorControllerServer::executeCB, this);
}

void MotorControllerServer::executeCB(const sparkfun_tb6612fng_controller::MotorCommand::ConstPtr& msg)
{
    bool direction = msg->direction;
    float speed = msg->speed;
    int8_t motor = msg->motor;
    
    ROS_INFO_STREAM("Recieved request: " <<
                    "(Dir: " << direction <<
                    ", Speed: " << speed <<
                    ", Motor: " << motor << ")");
    
    interface.send(direction, speed, motor);
}


MotorControllerServer::~MotorControllerServer()
{

}

