#ifndef EXIT_H
#define EXIT_H
#include "arlgentity.h"
namespace age {

class Exit : public ARLGEntity {
public:
    Exit(ARLG &game, Location l);
    ~Exit() {}

private:
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
