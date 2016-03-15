#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <sparkfun_tb6612fng_controller/MotorCommandAction.h>

namespace sf = sparkfun_tb6612fng_controller;

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "sparkfun_motor_test");
    ros::NodeHandle node;
    ros::Rate r(20);
    
    actionlib::SimpleActionClient<sf::MotorCommandAction> client("sparkfun_tb6612fng_controller/front", true);
    
    while(ros::ok()) {
        sf::MotorCommandGoal goal;
        goal.direction = true;
        goal.speed = 1;
        goal.motor = 0;
        
        ROS_INFO("Sending goal...");
        client.sendGoalAndWait(goal);
        ROS_INFO("Sent");
        ros::spinOnce();
        r.sleep();
    }
    
    sf::MotorCommandGoal goal;
    goal.direction = true;
    goal.speed = 0;
    goal.motor = 0;
    
    client.sendGoalAndWait(goal);
    
    return 0;
}