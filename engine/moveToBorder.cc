#include "moveToBorder.h"
#include "constants.h"
namespace age {

MoveToBorder::MoveToBorder(MoveToBorderDirection d): d{d} {}

Location MoveToBorder::nextMove(Location l, long numTicks) {
    switch (d) {
        case MoveToBorderDirection::MOVE_LEFT_BORDER:
            l.x -= 1;
            break;

        case MoveToBorderDirection::MOVE_RIGHT_BORDER:
            l.x += 1;
            break;

        case MoveToBorderDirection::MOVE_TOP_BORDER:
            l.y -= 1;
            break;

        case MoveToBorderDirection::MOVE_BOTTOM_BORDER:
            l.y += 1;
            break;
    }
    return l;
}

}
