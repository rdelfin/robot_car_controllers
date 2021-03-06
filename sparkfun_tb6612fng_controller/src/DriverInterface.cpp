#include <sparkfun_tb6612fng_controller/DriverInterface.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <ros/ros.h>

namespace sf_motor {
    DriverInterface::DriverInterface(int pwmAPin, int dir1APin, int dir2APin, int pwmBPin, int dir1BPin, int dir2BPin, int standbyPin)
        : pwmAPin(pwmAPin), dir1APin(dir1APin), dir2APin(dir2APin), 
          pwmBPin(pwmBPin), dir1BPin(dir1BPin), dir2BPin(dir2BPin),
          standbyPin(standbyPin)
    {
        softPwmCreate(pwmAPin, 0, 100);
        softPwmCreate(pwmBPin, 0, 100);
        pinMode(dir1APin, OUTPUT);
        pinMode(dir2APin, OUTPUT);
        pinMode(dir1BPin, OUTPUT);
        pinMode(dir2BPin, OUTPUT);
        pinMode(standbyPin, OUTPUT);
    }
    
    void DriverInterface::send(double speed, bool motor)
    {
        if(speed < -1) {
            speed = -1;
            ROS_WARN("Warning: Speed cannot be Less than 1. Raising to -1...");
            
        }
        
        if(speed > 1) {
            speed = 1;
            ROS_WARN("Warning: Speed cannot be more than 1. Lowering to 1...");
        }
        
        // More readable than if(motor)
        if(motor == 0) {
            digitalWrite(dir1APin, (speed < 0) ? HIGH : LOW);
            digitalWrite(dir2APin, (speed < 0) ? LOW: HIGH);
            softPwmWrite(pwmAPin, (int)(fabs(speed) * 100));
        }
        else {
            digitalWrite(dir1BPin, (speed < 0) ? HIGH : LOW);
            digitalWrite(dir2BPin, (speed < 0) ? LOW: HIGH);
            softPwmWrite(pwmBPin, (int)(fabs(speed) * 100));
        }
        
        digitalWrite(standbyPin, HIGH);
    }

    DriverInterface::~DriverInterface()
    {
        digitalWrite(dir1APin, LOW);
        digitalWrite(dir2APin, LOW);
        digitalWrite(dir1BPin, LOW);
        digitalWrite(dir2BPin, LOW);
        digitalWrite(standbyPin, LOW);
        softPwmWrite(pwmAPin, 0);
        softPwmWrite(pwmBPin, 0);
        softPwmStop(pwmAPin);
        softPwmStop(pwmBPin);
    }

}
