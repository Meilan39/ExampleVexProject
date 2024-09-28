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

/*----------------------------------------------------------------------------*/
/* this function when the program turns on                                    */
/* ensure that there are no infinite loops here                               */
/* initialize sensors, subsystems, etc                                        */
/*----------------------------------------------------------------------------*/
void pre_auton(void) {

}

/*----------------------------------------------------------------------------*/
/* this function runs when the competition switch enables autonomous          */
/* ensure that there are no infinite loops here                               */
/* initialize sensors, subsystems, etc                                        */
/*----------------------------------------------------------------------------*/
void autonomous(void) {
  // this just means you don't have to write select::left instead of autos::select::left etc.
  // when used within brackets, the namespace only applies within the brackets of the "autonomous" function
  using namespace autos;

  // the switch statement is like a long if-elif-elif... statement
  switch(autoSelect) {
    case select::left : left(); break;
  }
  right();    

}

void usercontrol(void) {
  while(1) {
    wait(20, msec); 
  }
}


int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while(1) { wait(100, msec); }
}
