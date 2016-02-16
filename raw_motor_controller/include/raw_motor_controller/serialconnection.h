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

#pragma once

#include <stdio.h>
#include <string>
#include <sstream>
#include <termios.h>

class SerialConnection
{
public:
    SerialConnection();
    SerialConnection(const std::string& device_name, int baud_rate);
    
    void send_data(const std::string&);
    
    bool recieve_data(std::stringbuf &buffer);
    char recieve_character();
    // TODO: Implement a timeout mechanism
    bool recieve_line(std::stringbuf &buffer);
    
    ~SerialConnection();
    
private:
    int fd;
    FILE* fstream;
    std::string device_name;
};
