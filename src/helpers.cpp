#include "vex.h"

double wrap(double current, double desired) {
    double error = current - desired;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    return -error;
}

double bound(double angle) {
    return fmod( fmod(angle, 360) + 360, 360 );
}