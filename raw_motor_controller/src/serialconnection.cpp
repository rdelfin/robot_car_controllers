/*
 * Copyright 2016 Ricardo Delfin Garcia <ricardo.delfin.garcia@gmail.com>
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
    options.c_cflag = baud_rate | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
    
    fstream = fdopen(fd, "rw");
}

bool SerialConnection::recieve_data(std::stringstream& buffer)
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
    
    buffer << rx_buffer;
    return true;
}

char SerialConnection::recieve_character()
{
    return fgetc(fstream);
}

bool SerialConnection::recieve_line(std::stringstream &buffer)
{
    char c;
    while((c = fgetc(fstream)) != '\n') {
        // Default value for UART streams (I think...)
        if(c != 255)
            buffer.put(c);
    }
    
    // TODO: Implement return false on timeout event.
    return true;
}

bool SerialConnection::send_data(const std::string &data)
{
    int written_bytes = write(fd, data.c_str(), data.length());
    return written_bytes == data.length();
}


SerialConnection::~SerialConnection()
{
    close(fd);
}
