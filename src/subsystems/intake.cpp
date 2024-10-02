#include "subsystems/intake.h"

void Intake::init() {
    intake.setStopping(brake);
    conveyor.setStopping(brake);
    clampP.close();
}

void Intake::stop() {
    intake.stop();
    conveyor.stop();
}

void Intake::in() {
    intake.spin(forward, 100, pct);
    conveyor.spin(forward, 100, pct);
}

void Intake::out() {
    intake.spin(reverse, 100, pct);
    conveyor.spin(reverse, 100, pct);
}

void Intake::clamp() {
    if(clampState) return;
    clampP.close();
}

void Intake::unclamp() {
    if(!clampState) return;
    clampP.open();
}