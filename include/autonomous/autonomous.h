#ifndef AUTONOMOUS
#define AUTONOMOUS

#include "dead.h"
#include "left.h"
#include "right.h"
#include "skills.h"

namespace autos {
    enum class select {
        left = 0,
        right = 1,
        dead = 2,
        skills = 3
    };
}

#endif