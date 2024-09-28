#ifndef INTAKE
#define INTAKE

    #include "vex.h"

    using namespace vex;

    class Intake {
     private:
        vex::motor intake {port::intake};
        vex::pneumatics clampL {port::clampL};
        vex::pneumatics clampR {port::clampR};
        // clamp state to save air?
        bool clampState = false;
     public:
        void init();
        void stop();
        void in();
        void out();
        void clamp();
        void unclamp();
    };

#endif