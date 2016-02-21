/*
 * Copyright 2016 <copyright holder> <email>
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

#include "raw_motor_controller/motorcommandserver.h"

MotorCommandServer::MotorCommandServer(std::string name)
    : name(name),
    server(nh, name, boost::bind(&MotorCommandServer::executeCB, this, _1), false)
{
    server.start();
    ROS_INFO_STREAM("Motor Command actionlib server created with name" << name);
}


void MotorCommandServer::executeCB(const raw_motor_controller::MotorCommandGoalConstPtr& goal)
{
    ROS_INFO("RECIECED GOAL WITH DATA:\n\tDevice: \"%s\"\n\tDirection (1 or 2): %d\n\tPower: %d\n\tMotor: %d",
             goal->device.c_str(), (int)goal->direction, (int)goal->power, (int)goal->motor);
    
    // The file has not been opened. Create a new connection
    if(connections.find(goal->device) ==  connections.end()) {
        ROS_INFO("Connection to device created");
        connections[goal->device] = MotorConnection(goal->device);
    }
    
    if(!correctGoal(goal)) {
        feedback.error = true;
        server.publishFeedback(feedback);
    }
    
    bool success = connections[goal->device].sendAction((motor_speed_t)goal->power,
                                                        (direction_t)goal->direction,
                                                        (motor_id_t)goal->motor);
    
    if(!success) {
        ROS_INFO("There was an error servicing request.");
    }
    
    
    result.successful = success;
    
    server.setSucceeded(result);
}

bool MotorCommandServer::correctGoal(const raw_motor_controller::MotorCommandGoalConstPtr& goal)
{
    // Direction is one of the possible values
    if(goal->direction != goal->FORWARD && goal->direction != goal->BACKWARD)
        return false;
    
    // Only left and right motors are valid
    if(goal->motor != goal->LEFT && goal->motor != goal->RIGHT)
        return false;
    
    // The power must be an integer between 0 and 9 inclusive
    if(goal->power < 0 || goal->power > 9)
        return false;
    
    return true;
}

MotorCommandServer::~MotorCommandServer()
{

}
