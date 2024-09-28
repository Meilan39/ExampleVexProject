#include "subsystems/base.h"

/* @brief get the heading of the gyro
 * @return the heading of the gyro in degrees (0 ~ 360 clockwise)
 */
double Base::getGyro() {
    return Inertial.heading(degrees);
}

/* @brief set the gyro angle to "heading"
 * @param heading angle to set the heading (0 ~ 360 clockwise)
 */
void Base::setGyro(double heading) {
    Inertial.setHeading(heading, degrees);
}

/* @brief initialize the drive base in pre-auton */
void Base::init() {
    // begin calibrating the inertial sensor
    Inertial.calibrate();
    // set the stopping mode of the drive motors to brake mode
    FR.setStopping(brake);
    FL.setStopping(brake);
    RR.setStopping(brake);
    RL.setStopping(brake);
    // wait for the inertial sensor to stop calibrating
    while(Inertial.isCalibrating()) {wait(100, msec);}
}

/* @brief rotate the drive base to "angle" 
 * @param angle angle in degrees to rotate the drive motors to
 * @return boolean for if the drive is rotating or not
 */
bool Base::rotateTo(double angle) {
    if(moving) { // the drive is rotating
        double error = wrap(getGyro(), angle);
        if(fabs(error) < 1) inRangeCount++;
        teleop(0, pid.get(error, 0));     
        moving = inRangeCount < 5; 
        return moving; 
    } else { // the drive is not rotating
        pid.reset();
        inRangeCount = 0;  
        moving = true;
        return true;       
    }
}

/* @brief move the drive base forward or backward by "position" at "speed" 
 * @param position position in degrees to rotate the drive motors to
 * @param speed in rotations per minute
 * @return boolean for if the drive is moving or not
 */
bool Base::moveTo(double position, double speed) {
    if(moving) { // if the drive is moving
        moving = (FR.isSpinning()||FL.isSpinning()||RR.isSpinning()||RL.isSpinning());
        return moving;
    } else { // if the drive is not moving
        speed *= MAX_RPM;
        FR.spinToPosition(position, deg, speed, rpm, false);
        FL.spinToPosition(position, deg, speed, rpm, false);
        RR.spinToPosition(position, deg, speed, rpm, false);
        RL.spinToPosition(position, deg, speed, rpm, false);
        moving = true;
        return true;        
    }
}

/* @brief arcade drive for teleop 
 * @param y (-1 backward ~ 1 forward)
 * @param x (-1 left ~ 1 right)
 */
void Base::teleop(double y, double w) {
    double right = y + w;
    double left  = y - w;
    double max   = fmax( fmax( fabs(right), 1 ), left ); // max between 1, abs(right), abs(left)
    right = right/max * MAX_RPM;
    left = left/max * MAX_RPM;
    FR.spin(forward, right, rpm);
    FL.spin(forward, left , rpm);
    RR.spin(forward, right, rpm);
    RL.spin(forward, left , rpm); 
}
