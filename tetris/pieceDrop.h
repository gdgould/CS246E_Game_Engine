#ifndef PIECEDROP_H
#define PIECEDROP_H
#include "../engine/movePlayerControlled.h"
#include <cstdlib>
namespace age {

class PieceDrop : public MovePlayerControlled {
    int gravity;
    bool inSoftDrop;
    int cellsInSoftDrop;

public:
    PieceDrop(int gravity);
    Location nextMove(Location l, Action a, long numTicks) override;

    int getSoftDropScore();
};
}

#endif
