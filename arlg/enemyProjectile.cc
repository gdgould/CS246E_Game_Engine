#include "enemyProjectile.h"
namespace age {

EnemyProjectile::EnemyProjectile(ARLG &game, Location l, ARLG::Direction d): ARLGEntity(game, -1, EntityType::BOSSPROJ, l) {
    this->hasHealth = false;
    this->setTexture(Texture(1, 1, 'O', Location{0,0}, ENEMY_PROJECTILE_COLOR));
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

void EnemyProjectile::doUpdate(Action a, Action prev, long numTicks) {
    
}

void EnemyProjectile::doDraw(View &v) {

}

void EnemyProjectile::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::PLAYER: this->shouldDespawn = true; break;
            default: break;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
