#include "health.h"
namespace age {

Health::Health(ARLG &game, Location l): ARLGEntity(game, -1, EntityType::HEALTH, l) {
    this->setTexture(Texture{ 1, 1, 'h'});
    this->hasHealth = false;
}

void Health::doUpdate(Action a, Action prev, long numTicks) {

}

void Health::doDraw(View &v) {

}

void Health::doOtherColliding(const Entity &other, Location before, Location after) {
        try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        if (o.getHasHealth()) {
            this->shouldDespawn = true;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
