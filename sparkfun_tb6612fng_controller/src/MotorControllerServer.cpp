#include <sparkfun_tb6612fng_controller/MotorControllerServer.h>

MotorControllerServer::MotorControllerServer(std::string name)
    : server(nh, name, boost::bind(&MotorControllerServer::executeCB, this, _1), false),
      action_name(name)
{
    server.start();
}

void MotorControllerServer::executeCB(const sparkfun_tb6612fng_controller::MotorCommandGoalConstPtr& goal)
{
    bool direction = goal->direction;
    float speed = goal->speed;
    int8_t motor = goal->motor;
    
    result.successful = true;
    
    server.setSucceeded(result);
}


MotorControllerServer::~MotorControllerServer()
{

}

