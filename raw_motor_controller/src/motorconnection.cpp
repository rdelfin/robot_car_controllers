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

#include "raw_motor_controller/motorconnection.h"

#include <ros/ros.h>



MotorConnection::MotorConnection()
{

}

// As per the specification, the baud rate MUST be 115200 baud
MotorConnection::MotorConnection(const std::string& device_name)
    : SerialConnection(device_name, B115200)
{
    sendAction(PWM_OFF, FORWARD, MOTOR_LEFT);
    sendAction(PWM_OFF, FORWARD, MOTOR_RIGHT);
}

/* Format for a message has 4 characters: "MDV\r" -
 *   M  - Motor number: Either 1 or 2.
 *   D  - Motor direction: Either f (forward) or r (reverse) case-insensitive.
 *   V  - Motor velocity. From '0' (stopped, or 0% PWM) through '9' (100% PWM).
 *   \r - Cartridge return character. Used as delimiter.
 */
bool MotorConnection::sendAction(motor_speed_t speed, direction_t direction, int motor_number)
{
    if(speed < PWM_OFF || speed > PWM_9) {
        ROS_ERROR_STREAM("SEND ACTION: Motor speed " << speed << " is invalid");
        return false;
    }
    
    if(direction != FORWARD && direction != BACKWARD) {
        ROS_ERROR_STREAM("SEND ACTION: Motor direction " << direction << " is invalid");
        return false;
    }
    
    if(motor_number != MOTOR_LEFT && motor_number != MOTOR_RIGHT) {
        ROS_ERROR_STREAM("SEND ACTION: Motor number " << motor_number << " is invalid");
        return false;
    }
    
    std::stringstream msg, rx_buffer;
    
    msg.put(motor_number == MOTOR_LEFT ? '1' : '2');  // Motor number:    M
    msg.put(direction == FORWARD ? 'f' : 'r');        // Motor direction: D
    msg.put('0' + speed);                             // Motor velocity:  V
    msg.put('\r');                                    // Delimiter (cartridge return)
    
    ROS_INFO()
    if(!send_data(msg.str())) {
        ROS_ERROR_STREAM("SEND ACTION: Failed to send data: " << msg.str());
        return false;
    }
    
    bool resend = false;
    
    do {
        rx_buffer.str("");
        
        // Recieve first line: Always a repetition of the command.
        if(!recieve_line(rx_buffer)) {
            ROS_ERROR_STREAM("SEND ACTION: Failed to recieve response. Exiting...");
            return false;
        }
        
        if(rx_buffer.str()[0] != '>' && rx_buffer.str().substr(0, 2) != msg.str().substr(0, 2)) {
            ROS_ERROR_STREAM("SEND ACTION: Recieved unexpected response \"" << rx_buffer.str().substr(0, 2) << "\". Exiting...\n");
            return false;
        }
        
        rx_buffer.str("");
        
        // Recieve second line: Either an error message or a POSITIVE number (tested).
        if(!recieve_line(rx_buffer)) {
            ROS_ERROR_STREAM("SEND ACTION: Failed to recieve response. Exiting...");
            return false;
        }
        
        // We recieced a digit, meaning the message was sent.
        if(isdigit(rx_buffer.str()[0])) {
            resend = false;
        }
        
        // Otherwise, this is an error message. The next line will be a digit, so we need to ignore it and resend.
        else {
            if(!recieve_line(rx_buffer)) {
                ROS_ERROR_STREAM("SEND ACTION: Failed to recieve response. Exiting...");
                return false;
            }
            
            resend = true;
        }
        
    } while(resend);
    
    
    return true;
}


MotorConnection::~MotorConnection()
{

}
