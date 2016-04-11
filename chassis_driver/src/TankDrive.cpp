#include <chassis_driver/TankDrive.h>
#include <sparkfun_tb6612fng_controller/MotorCommand.h>

namespace sf = sparkfun_tb6612fng_controller;

TankDrive::TankDrive()
{

}

TankDrive::TankDrive(std::string frontTopic, std::string backTopic)
{
    frontPub = nh::advertise<sf::MotorCommand>(frontTopic, 10);
    backPub = nh::advertise<sf::MotorCommand>(backTopic, 10);
}

TankDrive::drive(double left, double right)
{
    sf::MotorCommand msgFrontLeft, msgFrontRight, msgBackLeft, msgBackRight;
    
    msgFrontLeft.speed = left;
    msgFrontLeft.motor = 0;
    
    msgFrontRight.speed = right;
    msgFrontRight.motor = 1;
    
    msgBackLeft.speed = left;
    msgBackLeft.motor = 0;
    
    msgBackRight.speed = right;
    msgBackRight.motor = 1;
    
    
    frontPub.publish(msgFrontLeft);
    frontPub.publish(msgFrontRight);
    backPub.publish(msgBackLeft);
    backPub.publish(msgBackRight);
    
}

TankDrive::~TankDrive()
{

}
