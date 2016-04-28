#include <ros/ros.h>

#include <sparkfun_tb6612fng_controller/MotorCommand.h>

namespace sf = sparkfun_tb6612fng_controller;

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "sparkfun_motor_test");
    ros::NodeHandle node;
    ros::Rate r(20);
    
    ros::Publisher publisher = node.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/front", 100);
    ros:: Publisher publisher2 = node.advertise<sf::MotorCommand>("sparkfun_tb6612fng_controller/back", 100);
    while(ros::ok()) {
        sf::MotorCommand msg;
        msg.speed = 1;
        msg.motor = 0;
        
        publisher.publish(msg);
        publisher2.publish(msg);
        msg.motor =  1;
        
        publisher.publish(msg);
        publisher2.publish(msg);

        ros::spinOnce();
        r.sleep();
    }
    
    sf::MotorCommand msg;
    msg.speed = 0;
    msg.motor = 0;
    
    publisher.publish(msg);
    publisher2.publish(msg);
    msg.motor = 1;
    
    publisher.publish(msg);
    publisher2.publish(msg);

    return 0;
}
