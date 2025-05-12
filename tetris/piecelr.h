#ifndef PIECELR_H
#define PIECELR_H
#include "../engine/movePlayerControlled.h"
#include <cstdlib>
namespace age {

class PieceLR : public MovePlayerControlled {
    uint dasDelay, repeatRate;
    bool inDas;
    int dasCounter;

public:
    PieceLR(uint dasDelay, uint repeatRate);
    Location nextMove(Location l, Action a, long numTicks) override;
};
}

#endif
