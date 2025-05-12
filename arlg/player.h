#ifndef PLAYER_H
#define PLAYER_H
#include "arlgentity.h"
namespace age {

class Player : public ARLGEntity {
    int projectileCountdown;
public:
    Player(ARLG &game, Location l);
    ~Player() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
