#include "playerMove.h"
#include "keytype.h"
#include <cmath>
namespace age {

PlayerMove::PlayerMove() {}

Location PlayerMove::nextMove(Location l, Action a, long numTicks) {
    if (KeyDown(a, Keytype::LEFT)) { --l.x; }
    else if (KeyDown(a, Keytype::RIGHT)) { ++l.x; }
    else if (KeyDown(a, Keytype::UP)) { --l.y; }
    else if (KeyDown(a, Keytype::DOWN)) { ++l.y; }

    return l;
}

}
