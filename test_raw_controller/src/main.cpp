#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <raw_motor_controller/MotorCommandAction.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "test_raw_controller");
    
    actionlib::SimpleActionClient<raw_motor_controller::MotorCommandAction> client("controllers/raw_motor", true);
    
    ROS_INFO("Waiting for actionlib server...");
    client.waitForServer();
    
    raw_motor_controller::MotorCommandGoal goal;
    goal.device = "/dev/ttyAMA0";
    goal.direction = goal.FORWARD;
    goal.motor = goal.LEFT;
    goal.power = 0;
    
    // Send zero speed to front left motor
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    // Send zero speed to fron right motor
    goal.motor = goal.RIGHT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    // Send zero speed to back right motor
    goal.device = "/dev/ttyUSB0";
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    // Send zero speed to back left motor
    goal.motor = goal.LEFT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    // Set max power to back left motor
    goal.power = 9;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.motor = goal.RIGHT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.device = "/dev/ttyAMA0";
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.motor = goal.LEFT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.power = 0;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.motor = goal.RIGHT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.device = "/dev/ttyUSB0";
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
    
    goal.motor = goal.LEFT;
    client.sendGoal(goal);
    client.waitForResult(ros::Duration(30.0));
}