#ifndef MOVELINE_H
#define MOVELINE_H
#include "movementAction.h"
#include <cstdlib>
namespace age {

class MoveLine : public MovementAction {
    int x, y;
    uint ticks;
public:

    MoveLine(int x, int y, uint ticks);
    Location nextMove(Location l, long numTicks) override;
};
}
#endif
