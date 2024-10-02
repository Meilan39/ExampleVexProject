#ifndef BLUELEFT
#define BLUELEFT

    #include "vex.h"
    #include "subsystems/subsystems.h"

    namespace autos {

        void blue_left() {
            // start between 2nd and 3rd tile
            // start moving and unclamp
            for(int i = 0; base.moveTo(74.28, 0.8); i++) {
                if(i==2) intake.unclamp();
                wait(20, msec);
            }
            // clamp down on mobile goal
            intake.clamp();
            // rotate to blue-red stack
            base.rotateTo(111);
            // start moving and start intake
            for(int i = 0; base.moveTo(64.21, 0.8); i++) {
                if(i==10) intake.in();
                wait(20, msec);
            }
            // turn to face ladder
            base.rotateTo(270);
            // move to touch the ladder leg and stop the intake
            for(int i = 0; base.moveTo(110, 0.3); i++) {
                if(i==500) intake.stop();
                if(i > 1500) break;
                wait(20, msec);
            }
        }

    }

#endif


