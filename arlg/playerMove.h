#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H
#include "../engine/movePlayerControlled.h"
#include <cstdlib>
namespace age {

class PlayerMove : public MovePlayerControlled {

public:
    PlayerMove();
    Location nextMove(Location l, Action a, long numTicks) override;
};
}

#endif
