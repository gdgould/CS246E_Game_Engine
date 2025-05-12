#include "stalkerMove.h"
namespace age {

StalkerMove::StalkerMove(Player &p): player{p} {}

Location StalkerMove::nextMove(Location l, long numTicks) {
    if (numTicks % WALKER_FRAMES_PER_MOVE == 0) {
        if (l.x > player.location.x) { --(l.x); }
        else if (l.x < player.location.x) { ++(l.x); }

        if (l.y > player.location.y) { --(l.y); }
        else if (l.y < player.location.y) { ++(l.y); }
    }
    return l;
}

}
