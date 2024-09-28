#include "vex.h"

/* @brief return the most efficient direction to get from the current to desired angle
 * @param current the current angle in degrees (0 ~ 360)
 * @param desired the desired angle in degrees (0 ~ 360)
 * @return the angles to turn (-180 ~ 180)
 */
double wrap(double current, double desired) {
    double error = current - desired;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    return -error;
}

/* @brief take any angle and convert it so it is 0 to 360
 * @param angle angle to convert in degrees
 * @return the angle bounded to the range (0 ~ 360)
 */
double bound(double angle) {
    return fmod( fmod(angle, 360) + 360, 360 );
}

/* @brief if value is in range, return value, if not return min or max
 * @param value to fit to range (0 ~ 360)
 * @param min of the range (0 ~ 360)
 * @param max of the range (0 ~ 360)
 * @return value fit to range (min ~ max)
 */
double fitToRange(double value, double min, double max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}

/* @brief checks whether value is within setpoint (+ or -) threshold
 * @param value     value to check
 * @param setpoint  setpoint around which to expand threshold
 * @param threshold threshold around the setpoint to consider range
 * @return whether the value is in range of the setpoint threshold
 */
bool inRange(double value, double setpoint, double threshold) {
    return (setpoint - threshold < value) && (value < setpoint + threshold);
}

PID::PID(double p, double i, double d, double f) {
    this->p = p;
    this->i = i;
    this->d = d;
    this->f = f;
}
PID::PID(double p, double i, double d, double f, double min, double max) {
    this->p = p;
    this->i = i;
    this->d = d;
    this->f = f;
    this->min = min;
    this->max = max;
    range = true;
}
/* @brief get the PID output of the 
 * @param position current position of the mechanism
 * @param setpoint setpoint position of the mechanism
 * @return the output of the PID controller 
 */
double PID::get(double position, double setpoint) {
    double error = setpoint - position;
    double time = vex::timer::system();
    if (init) { // initialize the PID controller
        lastTime = time; 
        lastError = error; 
        accum = 0;
        init = false;
    }
    // divide by zero exception
    double dt = time - lastTime < 0.001 ? 0.001 : time - lastTime;
    double kp = p * error;
    double ki = i * (error * dt + accum);
    double kd = d * ((error - lastError) / dt);
    double kf = copysignf(f, error);
    lastTime = time;
    lastError = error;
    if (!range) return kp + ki + kd + kf;
    else return fitToRange(kp + ki + kd + kf, min, max);
}
/* reset the PID controller before new movement */
void PID::reset() {
    init = true;
}