#include "walker.h"
namespace age {

Walker::Walker(ARLG &game, Location l): ARLGEntity(game, 2, EntityType::WALKER, l), directionCounter{0}, currentDir{(ARLG::Direction)(rand() % 4)} {
    this->setTexture(Texture{ 2, 2, 'a'});
}

void Walker::doUpdate(Action a, Action prev, long numTicks) {
    --directionCounter;
    if (directionCounter <= 0) {
        // Choose a random direction North/South or East/West
        currentDir = (ARLG::Direction)(((rand() % 3) + (int)currentDir + 1) % 4);
        updateMovementPattern();
        directionCounter = (rand() % (maxChangeDir - minChangeDir)) + minChangeDir;
    }

    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Walker::updateMovementPattern() {
    clearMovementActions();
    switch (currentDir) {
        case ARLG::Direction::UP:
            this->addMovementAction(make_unique<MoveLine>(0, -1, WALKER_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::LEFT:
            this->addMovementAction(make_unique<MoveLine>(-1, 0, WALKER_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::DOWN:
            this->addMovementAction(make_unique<MoveLine>(0, 1, WALKER_FRAMES_PER_MOVE));
            break;
        case ARLG::Direction::RIGHT:
            this->addMovementAction(make_unique<MoveLine>(1, 0, WALKER_FRAMES_PER_MOVE));
            break;
    }
}

void Walker::doDraw(View &v) {

}

void Walker::doOtherColliding(const Entity &other, Location before, Location after) {
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
        // We've hit the border.
        location = getPrevLocation();
        currentDir = (ARLG::Direction)((currentDir + 2) % 4); // Flip up to down, etc.
        updateMovementPattern();
    }
}
}
