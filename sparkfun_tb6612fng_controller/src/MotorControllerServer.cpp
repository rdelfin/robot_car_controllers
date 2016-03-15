#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>

MotorControllerServer::MotorControllerServer(std::string name, int pwmPin, int dir1Pin, int dir2Pin, int standbyPin)
    : server(nh, name, boost::bind(&MotorControllerServer::executeCB, this, _1), false),
      action_name(name),
      interface(pwmPin, dir1Pin, dir2Pin, standbyPin)
{
    ROS_INFO("Starting server...");
    server.start();
    ROS_INFO("Started!");
}

void MotorControllerServer::executeCB(const sparkfun_tb6612fng_controller::MotorCommandGoalConstPtr& goal)
{
    bool direction = goal->direction;
    float speed = goal->speed;
    int8_t motor = goal->motor;
    
    ROS_INFO_STREAM("Recieved request: " <<
                    "(Dir: " << direction <<
                    ", Speed: " << speed <<
                    ", Motor: " << motor << ")");
    
    interface.send(direction, speed, motor);
    
    result.successful = true;
    server.setSucceeded(result);
}


MotorControllerServer::~MotorControllerServer()
{

}

