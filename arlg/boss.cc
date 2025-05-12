#include "boss.h"
namespace arlgart {

const char* bossPeaceful = R"""(    _____
  .'     '.
 /  o   o  \
|           |
|  \     /  |
 \  '---'  /
  '._____.'
)""";

const char* bossRage = R"""(    _____
  .'VVVVV'.
 /  o   o  \
|  '     '  |
|   .---.   |
 \  '---'  /
  '._____.'
)""";

}

namespace age {

Boss::Boss(ARLG &game, Location l): ARLGEntity(game, 50, EntityType::BOSS, l), stage{1}, moveLeft{true}, moveUp{true} {
    this->setTexture(Texture( std::string(arlgart::bossPeaceful) ));
    updateMovementPattern();
}

void Boss::doUpdate(Action a, Action prev, long numTicks) {
    game.statusLineThree = "Boss Health: " + std::to_string(health + 30 * (stage - 2));

    if (health == 30) {
        stage = 2;
        this->setTexture(Texture( std::string(arlgart::bossRage) ));
        updateMovementPattern();
    }
    if (rand() % BOSS_SPAWN_RATE == 0) {
        game.spawnBossEnemy(this->location, stage);
    }

    ARLGEntity::updateInvincible(); // Allows iFrames counter to function
}

void Boss::updateMovementPattern() {
    clearMovementActions();

    if (location.x <= LEFTBORDER + 1) {
        // We've hit the left border
        moveLeft = false;
    }
    else if (location.x >= RIGHTBORDER - spriteWidth - 1) {
        moveLeft = true;
    }

    if (location.y <= TOPBORDER + 1) {
        moveUp = false;
    }
    else if (location.y >= BOTTOMBORDER - spriteHeight - 1) {
        moveUp = true;
    }

    this->addMovementAction(make_unique<MoveLine>(moveLeft ? -1 : 1, moveUp ? -1 : 1, (stage == 1 ? BOSS_SPEED_STAGE1 : BOSS_SPEED_STAGE2)));
}

void Boss::doDraw(View &v) {

}

void Boss::doOtherColliding(const Entity &other, Location before, Location after) {
    try {
        const ARLGEntity& o = dynamic_cast<const ARLGEntity&>(other);

        switch (o.getType()) {
            case EntityType::HEALTH: ++health; break;
            case EntityType::PLAYERPROJ:
                if (!isInvincible()) {
                    --health; goInvincible();
                }
                if (health <= 0) { game.won(); }
                break;
            default: break;
        }
    }
    catch (...) {
        // We've hit the border.
        location = getPrevLocation();
        updateMovementPattern();
    }
}
}
