#include "subsystems/intake.h"

void Intake::init() {
    intake.setStopping(hold);
}

void Intake::stop() {
    intake.stop();
}

void Intake::in() {
    intake.spin(forward, 100, pct);
}

void Intake::out() {
    intake.spin(reverse, 100, pct);
}

void Intake::clamp() {
    if(clampState) return;
    clampL.open();
    clampR.open();
}

void Intake::unclamp() {
    if(!clampState) return;
    clampL.close();
    clampR.close();
}