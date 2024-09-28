#ifndef LEFT
#define LEFT

    #include "vex.h"
    #include "subsystems/subsystems.h"

    namespace autos {

        void left() {
            // using a 
            while(base.moveTo(100, 1)) {wait(20, msec);}

            for(int i = 0; base.moveTo(100, 1); i++) {
                if(i==5) //intake.spin();
                wait(20, msec);
            }
        }

    }

#endif