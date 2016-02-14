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

#include "raw_motor_controller/serialconnection.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


SerialConnection::SerialConnection()
{
    
}

SerialConnection::SerialConnection(const std::string& device_name, int baud_rate)
    : device_name(device_name)
{
    fd = open(device_name.c_str() , O_RDWR | O_NOCTTY | O_NDELAY);

    struct termios options;
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
}

bool SerialConnection::recieve_data(std::stringbuf& buffer)
{
    char rx_buffer[255];
    int len = read(fd, rx_buffer, 254);
    
    // A read returning -1 indicates an error and a return value of 0 indicates
    // no bytes read.
    if(len  == -1 || len == 0) {
        return false;
    }
    
    // We cannot count on read(2) to null-terminate the string
    rx_buffer[len] = '\0';
    
    buffer.sputn(rx_buffer, len);
    return true;
}

void SerialConnection::send_data(const std::string& data)
{
    int writter_bytes = write(fd, data.c_str(), data.length());
}


SerialConnection::~SerialConnection()
{
    close(fd);
}
