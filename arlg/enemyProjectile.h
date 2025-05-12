#ifndef ENEMY_PROJECTILE_H
#define ENEMY_PROJECTILE_H
#include "arlgentity.h"
namespace age {

class EnemyProjectile : public ARLGEntity {
public:
    EnemyProjectile(ARLG &game, Location l, ARLG::Direction d);
    ~EnemyProjectile() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};
}

#endif
