#ifndef HEALTH_H
#define HEALTH_H
#include "arlgentity.h"
namespace age {

class Health : public ARLGEntity {
public:
    Health(ARLG &game, Location l);
    ~Health() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
