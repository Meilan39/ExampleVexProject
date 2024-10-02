#ifndef BLUERIGHT
#define BLUERIGHT

    #include "vex.h"
    #include "subsystems/subsystems.h"

    namespace autos {

        void blue_right() {
            // start between 4th and 5th tile
            // start moving and unclamp
            for(int i = 0; base.moveTo(-74.28, 0.8); i++) {
                if(i==2) intake.unclamp();
                wait(20, msec);
            }
            // clamp down on mobile goal
            intake.clamp();
            // rotate to blue-red stack (360 - 111)
            base.rotateTo(249); 
            // start moving and start intake
            for(int i = 0; base.moveTo(64.21, 0.8); i++) {
                if(i==10) intake.in();
                wait(20, msec);
            }
            // turn to face ladder
            base.rotateTo(90);
            // move to touch the ladder leg and stop the intake
            for(int i = 0; base.moveTo(110, 0.3); i++) {
                if(i==500) intake.stop();
                if(i > 1500) break;
                wait(20, msec);
            }
        }

    }

#endif

// 

// 45.72 cm drive base
// 22.86 cm half of drive base
// a tile is 60 cm 
// a tile's diagonal is 84.85
// a tile's diagonal's half is 42.43

// 22.86 |____
//         60

// 60 |_____
//     82.86
// 180 - (arctan(60 / 82.86) * 180 / pi)