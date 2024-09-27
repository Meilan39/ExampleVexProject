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
        // rotation PID constants
        const double kP = 0.001;
     private:
        double getGyro();
        void   setGyro(double heading);
     public:
        void init();
        void stop();
        void rotateTo(double angle, double speed);
        void moveTo(double position, double speed);
        void teleop(float y, float w, bool ramp, bool slow = false);
    };

#endif