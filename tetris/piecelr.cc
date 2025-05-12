#include "piecelr.h"
#include "keytype.h"
#include <cmath>
namespace age {

PieceLR::PieceLR(uint dasDelay, uint repeatRate): dasDelay{dasDelay}, repeatRate{repeatRate}, inDas{false}, dasCounter{(int)dasDelay} {}

Location PieceLR::nextMove(Location l, Action a, long numTicks) {
    if (KeyDown(a, Keytype::LEFT) || KeyDown(a, Keytype::RIGHT)) {
        if (inDas) {
            --dasCounter;
            if (dasCounter <= 0) {
                l.x += KeyDown(a, Keytype::LEFT) ? -2 : 2;
                dasCounter = repeatRate;
            }
        }
        else {
            l.x += KeyDown(a, Keytype::LEFT) ? -2 : 2;
            inDas = true;
            dasCounter = dasDelay;
        }
    }
    else {
        inDas = false;
    }

    return l;
}

}
