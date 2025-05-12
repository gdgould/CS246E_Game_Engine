#ifndef FIRE_H
#define FIRE_H
#include "arlgentity.h"
namespace age {

class Fire : public ARLGEntity {
    const int minAnimateLength = 3;
    const int maxAnimateLength = 6;
    int animationCounter;
    bool lowercase;
public:
    Fire(ARLG &game, Location l);
    ~Fire() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
