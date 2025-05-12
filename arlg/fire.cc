#include "fire.h"
namespace age {

Fire::Fire(ARLG &game, Location l): ARLGEntity(game, -1, EntityType::FIRE, l), lowercase{true} {
    this->hasHealth = false;
    this->setTexture(Texture(1, 1, 'x'));
}

void Fire::doUpdate(Action a, Action prev, long numTicks) {
    --animationCounter;
    if (animationCounter <= 0) {
        lowercase = !lowercase;
        if (lowercase) { this->setTexture(Texture(1, 1, 'x')); }
        else { this->setTexture(Texture(1, 1, 'X')); }
        animationCounter = (rand() % (maxAnimateLength - minAnimateLength)) + minAnimateLength;
    }
}

void Fire::doDraw(View &v) {
    v.update(this->location, lowercase ? 'x' : 'X', 0);
}

void Fire::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        if (o.getType() == EntityType::PLAYERPROJ || o.getType() == EntityType::BOSSPROJ) {
            // Put out the fire and spawn a health pickup
            game.enemyDespawning(this->getType(), this->location);
            this->shouldDespawn = true;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
