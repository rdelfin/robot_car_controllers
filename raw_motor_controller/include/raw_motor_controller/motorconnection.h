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

#ifndef MOTORCONNECTION_H
#define MOTORCONNECTION_H

#include "serialconnection.h"

#include <string>

#define RX_ERROR_LENGTH "Incorrect Command Length"

typedef enum {
    PWM_OFF = 0,
    PWM_1 = 1,
    PWM_2 = 2,
    PWM_3 = 3,
    PWM_4 = 4,
    PWM_5 = 5,
    PWM_6 = 6,
    PWM_7 = 7,
    PWM_8 = 8,
    PWM_9 = 9
} motor_speed_t;

typedef enum {
    BACKWARD = 0,
    FORWARD = 1
} direction_t;

typedef enum {
    MOTOR_LEFT = 1,
    MOTOR_RIGHT = 2
} motor_id_t;


class MotorConnection : public SerialConnection
{
public:
    MotorConnection();
    MotorConnection(const std::string& device_name);
    
    bool sendAction(motor_speed_t, direction_t, int motor_number);
    
    ~MotorConnection();
};

#endif // MOTORCONNECTION_H
