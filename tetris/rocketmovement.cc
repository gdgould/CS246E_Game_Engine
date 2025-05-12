#include "rocketmovement.h"
namespace age {

RocketMovement::RocketMovement(long currentTicks): curTicks{currentTicks} {}

Location RocketMovement::nextMove(Location l, long numTicks) {
    if (numTicks - 120 > curTicks && numTicks % 10 == 0) { --l.y; }
    return l;
}

}
