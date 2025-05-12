#ifndef STALKER_H
#define STALKER_H
#include "arlgentity.h"
#include "player.h"
namespace age {

class Stalker : public ARLGEntity {
    Player *p;
public:
    Stalker(ARLG &game, Entity *p, Location l);
    ~Stalker() {}

private:
    void die();
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
