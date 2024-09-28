#include "vex.h"
#include "subsystems/subsystems.h"
#include "autonomous/autonomous.h"

// this just means you do not have can write pct instead of vex::percentUnits::pct, etc.
using namespace vex; 

/*----------------------------------------------------------------------------*/
/* define global variables here (refrain from making too many)                */
/*----------------------------------------------------------------------------*/

// this facilitates competition scheduling (do not delete)
competition Competition;
// this is an enumerator (word that resolves into an int) 
// it will hold an integer that represents what auto to run in autonomous
autos::select autoSelect;
// potentiometer
potV2 potentiometer = potV2(port::pot);


/*----------------------------------------------------------------------------*/
/* this function when the program turns on                                    */
/* ensure that there are no infinite loops here                               */
/* initialize sensors, subsystems, etc                                        */
/*----------------------------------------------------------------------------*/
void pre_auton(void) {
  base.init();
  intake.init();

  while(true) {
    Brain.Screen.clearScreen(); 
    Brain.Screen.setCursor(1, 3);
    Brain.Screen.print("left");
    Brain.Screen.setCursor(2, 3);
    Brain.Screen.print("right");
    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print("dead");
    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print("dead");    
    Brain.Screen.setCursor( potentiometer.angle(deg) , 1);
    Brain.Screen.print("~");
    wait(20, msec);    
  }
}

/*----------------------------------------------------------------------------*/
/* this function runs when the competition switch enables autonomous          */
/* ensure that there are no infinite loops here                               */
/* initialize sensors, subsystems, etc                                        */
/*----------------------------------------------------------------------------*/
void autonomous(void) {
  // the run the corresponding autonomous
  switch(autoSelect) {
    case autos::select::left : autos::left(); break;
    case autos::select::right : autos::right(); break;
    case autos::select::dead : autos::dead(); break;
    case autos::select::skills : autos::skills(); break;
    default : break;
  }
}

void usercontrol(void) {
  while(1) {
    // drive
    base.teleop(master.Axis3.value()/127, master.Axis1.value()/127);
    // intake
    if      (master.ButtonR1.pressing()) intake.in();
    else if (master.ButtonR2.pressing()) intake.out();
    else    intake.stop();
    // clamp
    if      (master.ButtonL1.pressing()) intake.clamp();
    else if (master.ButtonL1.pressing()) intake.unclamp();
    else    intake.stop();
    // sleep
    wait(20, msec); 
  }
}


int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while(1) { wait(100, msec); }
}
