#ifndef MOVEPLAYERCONTROLLED_H
#define MOVEPLAYERCONTROLLED_H
#include "movementAction.h"

namespace age {

class MovePlayerControlled : public MovementAction {
public:
    virtual Location nextMove(Location l, Action a, long numTicks) = 0;
    Location nextMove(Location l, long numTicks);
};
}

#endif
