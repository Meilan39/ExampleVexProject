#include "subsystems/base.h"

double Base::getGyro() {
    return Inertial.heading(degrees);
}

void Base::setGyro(double heading) {
    Inertial.setHeading(heading, degrees);
}

void Base::init() {
    // begin calibrating the inertial sensor
    Inertial.calibrate();
    // set the stopping mode of the drive motors to brake mode
    FR.setStopping(brake);
    FL.setStopping(brake);
    RR.setStopping(brake);
    RL.setStopping(brake);
    // wait for the inertial sensor to stop calibrating
    while(Inertial.isCalibrating()) { wait(100, msec); }
}

/* @brief move the drive base forward or backward by "position" at "speed" 
 * @param position position in degrees to rotate the drive motors to
 * @param speed in rotations per minute
 * */
void Base::moveTo(double position, double speed) {
    FR.spinToPosition(position, deg, speed, rpm, false);
    FL.spinToPosition(position, deg, speed, rpm, false);
    RR.spinToPosition(position, deg, speed, rpm, false);
    RL.spinToPosition(position, deg, speed, rpm, false);
}
