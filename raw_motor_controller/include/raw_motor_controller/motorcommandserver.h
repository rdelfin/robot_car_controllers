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

#pragma once

#include "raw_motor_controller/motorconnection.h"

#include <raw_motor_controller/MotorCommandAction.h>

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>

#include <string>
#include <unordered_map>

class MotorCommandServer
{
public:
    MotorCommandServer(std::string name);
    
    void executeCB(const raw_motor_controller::MotorCommandGoalConstPtr&);
    
    ~MotorCommandServer();

private:
    bool correctGoal(const raw_motor_controller::MotorCommandGoalConstPtr&);
    
    // this ordering is important (aparently)
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<raw_motor_controller::MotorCommandAction> server;
    
    std::string name;
    
    raw_motor_controller::MotorCommandFeedback feedback;
    raw_motor_controller::MotorCommandResult result;
    
    std::unordered_map<std::string, MotorConnection> connections;
};