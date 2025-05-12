#ifndef STALKERMOVE_H
#define STALKERMOVE_H
#include "../engine/movementAction.h"
#include "player.h"
#include <cstdlib>
namespace age {

class StalkerMove : public MovementAction {
    Player &player;

public:
    StalkerMove(Player &p);
    Location nextMove(Location l, long numTicks) override;
};
}

#endif
