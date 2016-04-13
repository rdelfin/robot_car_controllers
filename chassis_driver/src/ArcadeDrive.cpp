#include <chassis_driver/TankDrive.h>
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
    
    msgFrontLeft.speed = 0;
    msgFrontLeft.motor = 0;
    
    msgFrontRight.speed = 0;
    msgFrontRight.motor = 1;
    
    msgBackLeft.speed = 0;
    msgBackLeft.motor = 0;
    
    msgBackRight.speed = 0;
    msgBackRight.motor = 1;
    
    
    frontPub->publish(msgFrontLeft);
    frontPub->publish(msgFrontRight);
    backPub->publish(msgBackLeft);
    backPub->publish(msgBackRight);
}

ArcadeDrive::~ArcadeDrive()
{

}
