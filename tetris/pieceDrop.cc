#include "pieceDrop.h"
#include "keytype.h"
namespace age {

PieceDrop::PieceDrop(int gravity): gravity{gravity}, inSoftDrop{false}, cellsInSoftDrop{0} {}

Location PieceDrop::nextMove(Location l, Action a, long numTicks) {
    inSoftDrop = KeyDown(a, Keytype::DOWN);
    if (!inSoftDrop) { cellsInSoftDrop = 0; }

    if (inSoftDrop && gravity >= 2) {
        if (numTicks % 2 == 0) {
            ++l.y;
            ++cellsInSoftDrop;
        }
    }
    else if (numTicks % gravity == 0) { ++ l.y; }

    return l;
}

int PieceDrop::getSoftDropScore() { return cellsInSoftDrop; }

}
