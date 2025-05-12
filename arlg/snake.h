#ifndef SNAKE_H
#define SNAKE_H
#include "arlgentity.h"
namespace age {

class Snake : public ARLGEntity {
const vector<string> sprites {"Z\nz\nz\nz", "Zzzz", "z\nz\nz\nZ", "zzzZ" };
ARLG::Direction direction;

public:
    Snake(ARLG &game, Location l);
    ~Snake() {}

private:
    void changeDirection();
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doOtherColliding(const Entity &other, Location before, Location after) override;
};

}
#endif
