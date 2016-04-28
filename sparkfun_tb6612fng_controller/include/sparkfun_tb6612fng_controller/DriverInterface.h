#include <ros/ros.h>

namespace sf_motor {
    class DriverInterface {
    public:
        DriverInterface(int pwmAPin, int dir1APin, int dir2APin,
                        int pwmBPin, int dir1BPin, int dir2BPin,
                        int standbyPin);
        
        void send(double speed, bool motor);
        
        ~DriverInterface();
    private:
        int standbyPin;
        int pwmAPin, dir1APin, dir2APin;
        int pwmBPin, dir1BPin, dir2BPin;
        
    };
}
