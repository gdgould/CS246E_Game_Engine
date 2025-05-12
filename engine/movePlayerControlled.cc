#include "movePlayerControlled.h"
namespace age {

Location MovePlayerControlled::nextMove(Location l, long numTicks) {
    return nextMove(l, (Action)0, numTicks);
}
}
