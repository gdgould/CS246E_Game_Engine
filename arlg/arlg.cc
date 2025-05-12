#include "arlg.h"
#include "../engine/cursesview.h"
#include "../engine/cursescontrol.h"
#include <iostream>
#include <thread>
#include <ncurses.h>
// These can't be included in arlg.h -- they would form a cyclical include
#include "fire.h"
#include "health.h"
#include "player.h"
#include "playerProjectile.h"
#include "enemyProjectile.h"
#include "popup.h"
#include "snake.h"
#include "stalker.h"
#include "walker.h"
#include "exit.h"
#include "boss.h"
#include "art.h"


namespace age {

ARLG::ARLG(int level, bool enhanced): level{level} {
    if (level < 1 || level > 6) { this->level = 1; }
    AddView(std::move(make_unique<CursesView>(this->runningEnhanced())));
    AddController(std::move(make_unique<CursesKeyboard>()));
    this->collisionType = Game::CollisionType::Normal;
    this->borderCollide = true;
    this->setInputSmoothing(1);
    setFramerate(30);
    toggleEnhancements(enhanced);
    init_pair(PLAYER_PROJECTILE_COLOR, COLOR_RED, COLOR_BLACK); // player projectiles
    init_pair(ENEMY_PROJECTILE_COLOR, COLOR_GREEN, COLOR_BLACK); // Enemy projectiles

    srand(time(NULL));
    setupTextures();

    gameState = GameState::INTRO;
    levelClearCounter = LEVEL_CLEAR_DURATION;
}

void ARLG::setupTextures() {
    introScreen = Texture { std::string(arlgart::introScreen), Location{0,0}, " " };
    nextLevelScreen = Texture { std::string(arlgart::nextLevelScreen), Location{0,0}, " " };
    successScreen = Texture { std::string(arlgart::victory), Location{0,0}, " " };
    failureScreen = Texture { std::string(arlgart::defeat), Location{0,0}, " " };
}



Location ARLG::getRandomLocation() {
    return Location {rand() % (GAMEWIDTH - 4) + 2, rand() % (GAMEHEIGHT - 4) + 2};
}

void ARLG::spawnEntities() {
    Location playerloc = getRandomLocation();
    // Are we too close to the boss?
    while (level == 6 && (playerloc.distance(Location { 40, 10} ) < 10)) {
        playerloc = getRandomLocation();
    }
    unique_ptr<Player> p = make_unique<Player>(*this, playerloc);
    player = p.get();

    if (1 <= level && level <= 5) {
        Location exitloc = getRandomLocation();
        this->AddEntity(make_unique<Exit>(*this, exitloc));

        // Fires
        for (size_t i = 0; i < 4 + 2 * level + rand() % 8; i++)
        {
            Location temp = getRandomLocation();
            while (temp.distance(p->location) < 5) {
                temp = getRandomLocation();
            }
            this->AddEntity(make_unique<Fire>(*this, temp));
        }
        
        // Enemies
        for (size_t i = 0; i < 4 + level + rand() % 2; i++)
        {
            spawnRandomEnemy(player, exitloc);
        }
    }
    else if (level == 6) {
        this->AddEntity(make_unique<Boss>(*this, Location {40, 10}));
    }

    this->AddEntity(std::move(p));
}
void ARLG::spawnRandomEnemy(Entity* player, Location exitloc) {
int r = 0;
    switch (level) {
        case 1: r = 0; break;
        case 2: r = rand() % 2; break;
        case 3: r = 2 * (rand() % 2); break;
        case 4: r = 2 * (rand() % 2) + 1; break;
        case 5: r = rand() % 4; break;
        default: break;
    }
    Location temp = getRandomLocation();
    // Are we too close to the player or over the exit or too close to a wall while spawning a snake?
    while (temp.distance(player->location) < 5 || temp == exitloc ||
           (r == 3 && (temp.x > GAMEWIDTH - 3 || temp.y > GAMEHEIGHT - 3))) {
        temp = getRandomLocation();
    }

    switch (r) {
        case 0: 
            this->AddEntity(make_unique<Walker>(*this, temp));
            break;
        case 1: 
            this->AddEntity(make_unique<Stalker>(*this, player, temp));
            break;
        case 2: 
            this->AddEntity(make_unique<Popup>(*this, temp));
            break;
        case 3: 
            this->AddEntity(make_unique<Snake>(*this, temp));
            break;
    }
    ++spawnedEnemies;
}

bool ARLG::KeyUp(Keytype k) {
    return !KeyDown(getAction(), k) && KeyDown(getPrevAction(), k);
}


void ARLG::update() {
    switch (gameState) {
        case GameState::INTRO:
        case GameState::LEVELCLEAR:
            statusLineOne = "Level " + std::to_string(level) + "/6";
            --levelClearCounter;
            if (levelClearCounter <= 0) {
                gameState = GameState::PLAYING;
                levelClearCounter = 0;
                levelFreezeCounter = LEVEL_FREEZE_DURATION + LEVEL_DISPLAY_PLAYER_DURATION;
                spawnEntities();
                this->setEntityEnableState(false);
                this->setEntityVisibleState(false);
                if (player) { player->visible = true; }
            }
            break;
        case GameState::PLAYING:
            if (levelFreezeCounter == LEVEL_FREEZE_DURATION) {
                this->setEntityVisibleState(true);
                
            }
            if (levelFreezeCounter > 1) { --levelFreezeCounter; }
            else if (levelFreezeCounter == 1) {
                this->setEntityEnableState(true);
                levelFreezeCounter = 0;
            }
            break;
        case GameState::SUCCESS:
        case GameState::FAILURE:
            if (levelClearCounter > 0) { --levelClearCounter; } // Counter so that very quick inputs after the final screen is displayed don't count
            if (levelClearCounter <= 0 && getAction() != getPrevAction() && getAction() != (Action)0) { this->stop(); }
            break;
    }
}

void ARLG::draw(View &v) {
    switch (gameState) {
        case GameState::INTRO:
            introScreen.drawAt(v, Location {0,0}, 1);
            goto drawNonStatic;
        case GameState::LEVELCLEAR:
            nextLevelScreen.drawAt(v, Location {0,0}, 1);
        drawNonStatic:
            v.update(levelnumberLocation, std::to_string(level)[0], 2);
            v.update(countdownLocation, std::to_string(levelClearCounter / getFramerate() + 1)[0], 2);
            break;

        case GameState::PLAYING: break;
        case GameState::SUCCESS:
            successScreen.drawAt(v, Location {0,0}, 1);
            statusLineThree = "Boss Health: 0";
            break;
        case GameState::FAILURE:
            failureScreen.drawAt(v, Location {0,0}, 1);
            v.update(failLevelnumberLocation, std::to_string(level)[0], 2);
            break;
    }
}

void ARLG::onStart() {

    // Add startup code here (Optional)
}

void ARLG::onStop() {
    // Add stopping code here (Optional)
}


void ARLG::spawnPlayerProjectile(Location l, ARLG::Direction d) {
    this->AddEntity(make_unique<PlayerProjectile>(*this, l, d));
}
void ARLG::spawnEnemyProjectile(Location l, ARLG::Direction d) {
    this->AddEntity(make_unique<EnemyProjectile>(*this, l, d));
}
void ARLG::spawnBossEnemy(Location l, int state) {
    if (state == 1) {
        if (rand() % 2 == 0) { this->AddEntity(make_unique<Walker>(*this, l)); }
        else { this->AddEntity(make_unique<Stalker>(*this, player, l)); }
    }
    else if (state == 2) {
        int r = rand() % 4;
        switch (r) {
            case 0: 
                this->AddEntity(make_unique<Walker>(*this, l));
                break;
            case 1: 
                this->AddEntity(make_unique<Stalker>(*this, player, l));
                break;
            case 2: 
                this->AddEntity(make_unique<Popup>(*this, l));
                break;
            case 3: 
                this->AddEntity(make_unique<Snake>(*this, l));
                break;
        }
    }
}

int ARLG::getNumberofEnemies() { return spawnedEnemies; }

void ARLG::enemyDespawning(EntityType type, Location l) {
    switch (type) {
        case EntityType::PLAYER:
            // Loss
            break;
        case EntityType::FIRE:
            if (rand() % HEALTH_PICKUP_CHANCE == 0) {
                this->AddEntity(make_unique<Health>(*this, l));
            }
            break;
        case EntityType::STALKER:
            if (rand() % 4 == 0) {
                ++spawnedEnemies;
                this->AddEntity(make_unique<Walker>(*this, l));
            }
        case EntityType::WALKER:
        case EntityType::POPUP:
        case EntityType::SNAKE:
            --spawnedEnemies;
            break;
        case EntityType::BOSS:
            // Win
        default: break;
    }
}

void ARLG::completedLevel() {
    ++level;
    this->ClearEntities();
    gameState = GameState::LEVELCLEAR;
    levelClearCounter = LEVEL_CLEAR_DURATION;

}

void ARLG::lost() {
    this->ClearEntities();
    levelClearCounter = FINAL_SCREEN_CLEAR;
    gameState = GameState::FAILURE;
}

void ARLG::won() {
    this->ClearEntities();
    levelClearCounter = FINAL_SCREEN_CLEAR;
    gameState = GameState::SUCCESS;
}

}
