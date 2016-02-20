/*
 * Copyright 2016 Ricardo Delfin <ricardo.delfin.garcia@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include <ros/ros.h>

#include "raw_motor_controller/motorconnection.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "raw_motor_controller_node");
    
    ros::NodeHandle n;
    
    ros::Rate r(100);
    bool enable = false;
    MotorConnection front("/dev/ttyAMA0"), back("/dev/ttyUSB0");
    
    while(ros::ok()) {
        back.sendAction(PWM_9, FORWARD, MOTOR_RIGHT);
        back.sendAction(PWM_9, BACKWARD, MOTOR_LEFT);
        front.sendAction(PWM_9, FORWARD, MOTOR_RIGHT);
        front.sendAction(PWM_9, FORWARD, MOTOR_LEFT);
        
        ros::spinOnce();
        r.sleep();
    }
    
    back.sendAction(PWM_OFF, FORWARD, MOTOR_RIGHT);
    back.sendAction(PWM_OFF, FORWARD, MOTOR_LEFT);
    front.sendAction(PWM_OFF, FORWARD, MOTOR_RIGHT);
    front.sendAction(PWM_OFF, FORWARD, MOTOR_LEFT);
}