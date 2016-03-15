#include <sparkfun_tb6612fng_controller/DriverInterface.h>

namespace sf_motor {
    DriverInterface::DriverInterface(int pwmPin, int dir1Pin, int dir2Pin, int standbyPin)
        : pwmPin(pwmPin), dir1Pin(dir1Pin), dir2Pin(dir2Pin), standbyPin(standbyPin)
    {
        pinMode(pwmPin, PWM_OUTPUT);
        pinMode(dir1Pin, OUTPUT);
        pinMode(dir2Pin, OUTPUT);
        pinMode(standbyPin, OUTPUT);
        
        
        pwmSetMode(PWM_MODE_MS); 
        pwmSetClock(384);
        pwmSetRange(1000);
    }
    
    void DriverInterface::send(bool direction, double speed, bool motor)
    {
        digitalWrite(dir1Pin, direction ? HIGH : LOW);
        digitalWrite(dir2Pin, direction ? LOW: HIGH);
        digitalWrite(standbyPin, HIGH);
        pwmWrite(pwmPin, (int)(speed * 1024));
    }

    DriverInterface::~DriverInterface()
    {
        digitalWrite(dir1Pin, LOW);
        digitalWrite(dir2Pin, LOW);
        digitalWrite(standbyPin, LOW);
        pwmWrite(pwmPin, 0);
    }

}