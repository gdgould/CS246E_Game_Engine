#ifndef ROCKETMOVEMENT_H
#define ROCKETMOVEMENT_H
#include "../engine/movementAction.h"
#include <cstdlib>
namespace age {

class RocketMovement : public MovementAction {
    long curTicks;
public:
    RocketMovement(long currentTicks);
    Location nextMove(Location l, long numTicks) override;
};
}

#endif
