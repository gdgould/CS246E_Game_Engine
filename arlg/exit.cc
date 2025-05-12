#include "exit.h"
namespace age {

Exit::Exit(ARLG &game, Location l): ARLGEntity(game, -1, EntityType::EXIT, l) {
    this->hasHealth = false;
    this->setTexture(Texture(1, 1, 'e'));
    this->height = -1;
}

void Exit::doUpdate(Action a, Action prev, long numTicks) {
    if (this->game.getNumberofEnemies() == 0) {
        this->setTexture(Texture(1, 1, 'E'));
        this->height = 0;
    }
}

void Exit::doDraw(View &v) {
    
}

void Exit::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::PLAYER: 
                this->game.completedLevel();
                break;
            default: break;
        }
    }
    catch (...) {
        // Why is there another kind of entity?????
    }
}
}
