#include <ros/ros.h>
#include <wiringPi.h>

namespace sf_motor {
    class DriverInterface {
    public:
        DriverInterface(int pwmPin, int dir1Pin, int dir2Pin,
                        int standbyPin);
        
        void send(bool direction, double speed, bool motor);
        
        ~DriverInterface();
    private:
        int pwmPin, dir1Pin, dir2Pin, standbyPin;
        
    };
}