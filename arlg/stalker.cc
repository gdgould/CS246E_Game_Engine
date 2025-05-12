#include "stalker.h"
#include "stalkerMove.h"
namespace age {

// Dynamic cast here because the ARLG header cannot reference Player, only Entity
Stalker::Stalker(ARLG &game, Entity *p, Location l): ARLGEntity(game, 2, EntityType::STALKER, l), p{dynamic_cast<Player*>(p)} {
    this->setTexture(Texture{ 2, 2, 'b'});
    this->addMovementAction(make_unique<StalkerMove>(*(this->p)));
}

void Stalker::doUpdate(Action a, Action prev, long numTicks) {
    if (health <= 0) { die(); }
    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Stalker::doDraw(View &v) {

}

void Stalker::die() {

}

void Stalker::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::HEALTH: ++health; break;
            case EntityType::FIRE:
            case EntityType::PLAYERPROJ:
                if (!isInvincible()) {
                    --health; goInvincible();
                }
                if (health <= 0) { game.enemyDespawning(this->getType(), this->location); }
                break;
            default: break;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
