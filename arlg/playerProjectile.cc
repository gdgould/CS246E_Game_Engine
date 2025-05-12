#include "playerProjectile.h"
namespace age {

PlayerProjectile::PlayerProjectile(ARLG &game, Location l, ARLG::Direction d): ARLGEntity(game, -1, EntityType::PLAYERPROJ, l) {
    this->hasHealth = false;
    this->setTexture(Texture(1, 1, 'O', Location{0,0}, PLAYER_PROJECTILE_COLOR));
    switch (d) {
        case ARLG::Direction::UP:
            this->addMovementAction(make_unique<MoveLine>(0, -1, PROJECTILE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::LEFT:
            this->addMovementAction(make_unique<MoveLine>(-1, 0, PROJECTILE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::DOWN:
            this->addMovementAction(make_unique<MoveLine>(0, 1, PROJECTILE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::RIGHT:
            this->addMovementAction(make_unique<MoveLine>(1, 0, PROJECTILE_FRAMES_PER_MOVE));
            break;
    }
}

void PlayerProjectile::doUpdate(Action a, Action prev, long numTicks) {
    
}

void PlayerProjectile::doDraw(View &v) {

}

void PlayerProjectile::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::FIRE:
            case EntityType::WALKER:
            case EntityType::STALKER:
            case EntityType::POPUP:
            case EntityType::SNAKE:
            case EntityType::BOSS: this->shouldDespawn = true; break;
            default: break;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
