#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sparkfun_tb6612fng_controller/MotorCommand.h>

namespace sf = sparkfun_tb6612fng_controller;

void movebaseCallback(const geometry_msgs::TwistConstPtr&);

ros::Publisher frontPub, backPub;

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "move_base_node");
    
    ros::NodeHandle nh;
    
    ros::Subscriber move_base_sub = nh.subscribe("cmd_vel", 10, movebaseCallback);
    
    frontPub = nh.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/front", 10);
    backPub = nh.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/back", 10);
    
    ros::spin();
}

void movebaseCallback(const geometry_msgs::TwistConstPtr& msg)
{
    ROS_DEBUG_STREAM("Twist received. Speed: " << msg->linear.x << ". Rotation: " << msg->angular.z);
    
    double speed = msg->linear.x;
    double rotation = msg->angular.z;
    
    sf::MotorCommand msgFrontLeft, msgFrontRight, msgBackLeft, msgBackRight;
    
    msgFrontLeft.speed = speed + rotation;
    msgFrontLeft.motor = 0;
    
    msgFrontRight.speed = -(speed - rotation);
    msgFrontRight.motor = 1;
    
    msgBackLeft.speed = -(speed + rotation);
    msgBackLeft.motor = 0;
    
    msgBackRight.speed = speed - rotation;
    msgBackRight.motor = 1;
    
    
    frontPub.publish(msgFrontLeft);
    frontPub.publish(msgFrontRight);
    backPub.publish(msgBackLeft);
    backPub.publish(msgBackRight);
}
