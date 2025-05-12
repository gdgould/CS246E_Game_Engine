#ifndef WALKER_H
#define WALKER_H
#include "arlgentity.h"
namespace age {

class Walker : public ARLGEntity {
    int directionCounter = 0;
    const int minChangeDir = 30;
    const int maxChangeDir = 120;
    ARLG::Direction currentDir;
public:
    Walker(ARLG &game, Location l);
    ~Walker() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
    void updateMovementPattern();
};

}
#endif 
