#ifndef BOSS_H
#define BOSS_H
#include "arlgentity.h"
namespace age {

class Boss : public ARLGEntity {
    int stage;
    bool moveLeft;
    bool moveUp;
    const int spriteWidth = 13;
    const int spriteHeight = 7;
public:
    Boss(ARLG &game, Location l);
    ~Boss() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
    void updateMovementPattern();
};

}
#endif 
