#ifndef POPUP_H
#define POPUP_H
#include "arlgentity.h"
namespace age {

class Popup : public ARLGEntity {
bool invulnerable;
int invulnerableCounter;
const int minStateSwitch = 20;
const int maxStateSwitch = 60;
public:
    Popup(ARLG &game, Location l);
    ~Popup() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
