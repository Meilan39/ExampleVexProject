#include "vex.h"

/*  */
double wrap(double current, double desired) {
    double error = current - desired;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    return -error;
}

double bound(double angle) {
    return fmod( fmod(angle, 360) + 360, 360 );
}

double fitToRange(double value, double min, double max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}

double inRange(double value, double setpoint, double threshold) {
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
double PID::get(double position, double setpoint) {
    double error = setpoint - position;
    double time = vex::timer::system();
    // initialize the controller  
    if (init) {
        lastTime = time; // divide by zero exception
        lastError = error; 
        accum = 0;
        init = false;
    }
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
void PID::reset() {
    init = true;
}