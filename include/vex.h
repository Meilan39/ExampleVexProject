#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

extern brain Brain;
extern controller master;

namespace port {
  const int FR = vex::PORT7;
  const int FL = vex::PORT7;
  const int RR = vex::PORT2;
  const int RL = vex::PORT7;
  const int intake = vex::PORT10;
  const int inertial = vex::PORT7;
  const vex::triport::port& clampL = Brain.ThreeWirePort.F;
  const vex::triport::port& clampR = Brain.ThreeWirePort.D;
  const vex::triport::port& pot = Brain.ThreeWirePort.A;
}

double wrap(double current, double desired);
double bound(double angle);
double fitToRange(double value, double min, double max);
bool inRange(double value, double setpoint, double threshold);

class PID {
  private:
    double p;
    double i;
    double d;
    double f;
    double lastTime;
    double lastError;
    double accum;
    // reset control
    bool init = true;
    // range
    bool range = false;
    double min;
    double max;
  public:
    PID(double p, double i, double d, double f);
    PID(double p, double i, double d, double f, double min, double max);
    double get(double position, double setpoint);
    void reset();
};