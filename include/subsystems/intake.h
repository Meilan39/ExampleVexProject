#ifndef INTAKE
#define INTAKE

    #include "vex.h"
    
    using namespace vex;

    class Intake {
     private:
        vex::motor intake {port::intake};
        vex::motor conveyor {port::conveyor};
        vex::pneumatics clampP {Brain.ThreeWirePort.A};
        // clamp state to save air?
        bool clampState = true;
     public:
        void init();
        void stop();
        void in();
        void out();
        void clamp();
        void unclamp();
    };

#endif