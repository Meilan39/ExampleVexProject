#ifndef BASE
#define BASE

    #include "vex.h"

    using namespace vex;

    class Base {
     private:
        vex::motor FR {port::FR, ratio18_1, false};
        vex::motor FL {port::FL, ratio18_1, true };
        vex::motor RL {port::RL, ratio18_1, true };
        vex::motor RR {port::RR, ratio18_1, false};
        inertial Inertial {port::inertial};
        // rotation PID
        PID pid {0.008, 0, 0, 0.008, -1, 1};        
        // constants
        const double MAX_RPM = 200;        
        // state controller
        bool moving = false;
        int inRangeCount = 0;
     private:
        double getGyro();
        void   setGyro(double heading);
     public:
        void init();
        void stop();
        bool rotateTo(double angle);
        bool moveTo(double position, double speed);
        void teleop(double y, double w);
    };

#endif