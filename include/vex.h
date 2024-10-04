#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

extern vex::brain Brain;
extern vex::controller master;

extern vex::pneumatics clampP;

#ifndef HELPERS
#define HELPERS

  namespace port {
    const int FR = vex::PORT1;
    const int FL = vex::PORT2;
    const int RR = vex::PORT3;
    const int RL = vex::PORT4;
    const int MR = vex::PORT5;
    const int ML = vex::PORT6;
    const int intake = vex::PORT7;
    const int conveyor = vex::PORT8;
    const int inertial = vex::PORT11;
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

#endif