#ifndef MOVETOBORDER_H
#define MOVETOBORDER_H
#include "movementAction.h"
namespace age {

enum MoveToBorderDirection {MOVE_TOP_BORDER, MOVE_BOTTOM_BORDER, MOVE_LEFT_BORDER, MOVE_RIGHT_BORDER};

class MoveToBorder : public MovementAction {
        MoveToBorderDirection d;
public:
    MoveToBorder(MoveToBorderDirection d);
    Location nextMove(Location l, long numTicks) override;
};
}
#endif
