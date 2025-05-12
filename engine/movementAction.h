#ifndef MOVEMENTACTION_H
#define MOVEMENTACTION_H
#include "location.h"
#include "action.h"

namespace age {

class MovementAction {
public:
    virtual ~MovementAction() = default;
    virtual Location nextMove(Location l, long numTicks) {
        return l;
    }
};
}

#endif
