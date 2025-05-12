#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H
#include "arlgentity.h"
namespace age {

class PlayerProjectile : public ARLGEntity {
public:
    PlayerProjectile(ARLG &game, Location l, ARLG::Direction d);
    ~PlayerProjectile() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};
}

#endif
