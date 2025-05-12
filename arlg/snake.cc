#include "snake.h"
namespace age {

Snake::Snake(ARLG &game, Location l): ARLGEntity(game, 3, EntityType::SNAKE, l) {
    direction = (ARLG::Direction)(rand() % 4);
    changeDirection();
}

void Snake::doUpdate(Action a, Action prev, long numTicks) {
    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Snake::doDraw(View &v) {
    
}

void Snake::changeDirection() {
    direction = (ARLG::Direction)((direction + 2) % 4); // Flip up to down, etc.
    this->setTexture(Texture { sprites[direction] });
    this->clearMovementActions();
    switch (direction) {
        case ARLG::Direction::UP:
            this->addMovementAction(make_unique<MoveLine>(0, -1, SNAKE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::LEFT:
            this->addMovementAction(make_unique<MoveLine>(-1, 0, SNAKE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::DOWN:
            this->addMovementAction(make_unique<MoveLine>(0, 1, SNAKE_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::RIGHT:
            this->addMovementAction(make_unique<MoveLine>(1, 0, SNAKE_FRAMES_PER_MOVE));
            break;
    }
}

void Snake::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        if (o.getType() == EntityType::HEALTH) { ++health; return; }

        // Head-on collisions don't count:
        switch(direction) {
            case ARLG::Direction::UP: if (before.x == after.x && before.y <= location.y) { return; } break;
            case ARLG::Direction::DOWN: if (before.x == after.x && before.y >= location.y) { return; } break;
            case ARLG::Direction::LEFT: if (before.y == after.y && before.x <= location.x) { return; } break;
            case ARLG::Direction::RIGHT: if (before.y == after.y && before.x >= location.x) { return; } break;
        }

        switch (o.getType()) {
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
        // We've run into the border.
        location = getPrevLocation();
        changeDirection();
    }
}
}
