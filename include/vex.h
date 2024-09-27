#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

namespace port {
  const int FR = vex::PORT7;  
  const int FL = vex::PORT7; 
  const int RR = vex::PORT7;  
  const int RL = vex::PORT7;  
  const int inertial = vex::PORT7;
}

double wrap(double current, double desired);

double bound(double angle);