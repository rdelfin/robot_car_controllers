#include <chassis_driver/ArcadeDrive.h>
#include <sparkfun_tb6612fng_controller/MotorCommand.h>

namespace sf = sparkfun_tb6612fng_controller;

ArcadeDrive::ArcadeDrive()
    : frontPub(), backPub()
{

}

ArcadeDrive::ArcadeDrive(ros::Publisher* frontTopic, ros::Publisher* backTopic)
    : frontPub(frontTopic), backPub(backTopic)
{
    
}

void ArcadeDrive::drive(double speed, double rotation)
{
    sf::MotorCommand msgFrontLeft, msgFrontRight, msgBackLeft, msgBackRight;
    
    
    
    msgFrontLeft.speed = speed + rotation;
    msgFrontLeft.motor = 0;
    
    msgFrontRight.speed = speed - rotation;
    msgFrontRight.motor = 1;
    
    msgBackLeft.speed = speed + rotation;
    msgBackLeft.motor = 0;
    
    msgBackRight.speed = speed - rotation;
    msgBackRight.motor = 1;
    
    
    frontPub->publish(msgFrontLeft);
    frontPub->publish(msgFrontRight);
    backPub->publish(msgBackLeft);
    backPub->publish(msgBackRight);
}

ArcadeDrive::~ArcadeDrive()
{

}
