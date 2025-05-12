#include "popup.h"
namespace age {

Popup::Popup(ARLG &game, Location l): ARLGEntity(game, 4, EntityType::POPUP, l), invulnerable{false}, invulnerableCounter{0} {
    this->setTexture(Texture(1, 1, 'c'));
}

void Popup::doUpdate(Action a, Action prev, long numTicks) {
    --invulnerableCounter;
    if (invulnerableCounter <= 0) {
        invulnerable = !invulnerable;
        if (invulnerable) { this->setTexture(Texture(1, 1, 'c')); }
        else { this->setTexture(Texture(1, 1, 'D')); }
        invulnerableCounter = (rand() % (maxStateSwitch - minStateSwitch)) + minStateSwitch;
    }

    if (!invulnerable && numTicks % POPUP_PROJECTILE_COOLDOWN == 0) {
        game.spawnEnemyProjectile(location, ARLG::Direction::UP);
        game.spawnEnemyProjectile(location, ARLG::Direction::DOWN);
        game.spawnEnemyProjectile(location, ARLG::Direction::LEFT);
        game.spawnEnemyProjectile(location, ARLG::Direction::RIGHT);
    }

    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Popup::doDraw(View &v) {
    
}

void Popup::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::HEALTH: ++health; break;
            case EntityType::FIRE:
            case EntityType::PLAYERPROJ:
                if (!invulnerable && !isInvincible()) {
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
