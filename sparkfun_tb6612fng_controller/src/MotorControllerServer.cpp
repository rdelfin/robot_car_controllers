#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>

MotorControllerServer::MotorControllerServer(std::string name, int pwmPin, int dir1Pin, int dir2Pin, int standbyPin)
    : topic_name(name),
      interface(pwmPin, dir1Pin, dir2Pin, standbyPin)
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

