#include "moveline.h"
namespace age {

MoveLine::MoveLine(int x, int y, uint ticks): x{x}, y{y}, ticks{ticks} {}

Location MoveLine::nextMove(Location l, long numTicks) {
    if (numTicks % ticks == 0) { 
        return Location {l.x + x, l.y + y};
    }
    return l;
}

}
