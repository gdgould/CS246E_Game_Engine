#include "player.h"
#include "playerMove.h"
namespace age {

Player::Player(ARLG &game, Location l): ARLGEntity(game, 5, EntityType::PLAYER, l), projectileCountdown{0} {
    this->setTexture(Texture{ 1, 1, 'p'});
    this->addMovementAction(make_unique<PlayerMove>());
}

void Player::doUpdate(Action a, Action prev, long numTicks) {
    if (projectileCountdown <= 0) {
        projectileCountdown = PROJECTILE_COOLDOWN - 1;
        if (KeyDown(a, Keytype::SHOOTLEFT)) { this->game.spawnPlayerProjectile(this->location, ARLG::Direction::LEFT); }
        else if (KeyDown(a, Keytype::SHOOTRIGHT)) { this->game.spawnPlayerProjectile(this->location, ARLG::Direction::RIGHT); }
        else if (KeyDown(a, Keytype::SHOOTUP)) { this->game.spawnPlayerProjectile(this->location, ARLG::Direction::UP); }
        else if (KeyDown(a, Keytype::SHOOTDOWN)) { this->game.spawnPlayerProjectile(this->location, ARLG::Direction::DOWN); }
        else {
            projectileCountdown = 0;
        }
    }
    else {
        --projectileCountdown;
    }

    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Player::doDraw(View &v) {
    game.statusLineTwo = "Health: " + std::to_string(health);
}

void Player::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::NONE: break;
            case EntityType::PLAYERPROJ: break;
            case EntityType::HEALTH: ++health; break;
            case EntityType::FIRE:
            case EntityType::WALKER:
            case EntityType::STALKER:
            case EntityType::POPUP:
            case EntityType::SNAKE:
            case EntityType::BOSS:
            case EntityType::BOSSPROJ:
            if (!isInvincible()) {
                location = getPrevLocation() + (after - before) + (after - before); // Do the movement vector of what just hit us (knockback)
                --health; goInvincible();
            }
            if (health == 0) {
                game.statusLineTwo = "Health: 0";
                game.lost();
            }
            default: break;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
