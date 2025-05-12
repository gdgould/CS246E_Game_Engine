#ifndef ARLG_H
#define ARLG_H
#include "../engine/game.h"
#include "keytype.h"
namespace age {

enum EntityType {NONE, PLAYER, PLAYERPROJ, FIRE, EXIT, HEALTH, WALKER, STALKER, POPUP, SNAKE, BOSS, BOSSPROJ};
enum GameState {INTRO, PLAYING, LEVELCLEAR, SUCCESS, FAILURE};

const int HEALTH_PICKUP_CHANCE = 10; // There is a 1 in (this) chance of spawning a health pickup
const int WALKER_FRAMES_PER_MOVE = 4;
const int SNAKE_FRAMES_PER_MOVE = 3;
const int PROJECTILE_FRAMES_PER_MOVE = 2;
const int BOSS_SPEED_STAGE1 = 6;
const int BOSS_SPEED_STAGE2 = 4;
const int BOSS_SPAWN_RATE = 120; 

const int PLAYER_PROJECTILE_COLOR = 1;
const int ENEMY_PROJECTILE_COLOR = 2;
const int PROJECTILE_COOLDOWN = 10;
const int POPUP_PROJECTILE_COOLDOWN = 14;
const int IFRAMES = 12;

const int LEVEL_CLEAR_DURATION = 90;
const int FINAL_SCREEN_CLEAR = 30; // Timeout before the final screen can be cleared with any input
const int LEVEL_DISPLAY_PLAYER_DURATION = 30; // How long to display the player before showing other entities
const int LEVEL_FREEZE_DURATION = 30;  // After displaying other entities, how long before the game starts

class ARLG : public Game {
public:
enum Direction {UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3};
private:
    int spawnedEnemies = 0;
    int level;
    GameState gameState;
    Entity *player;
    int levelClearCounter = 0;
    int levelFreezeCounter = 0;

    Texture introScreen;
    Texture nextLevelScreen;
    Texture failureScreen;
    Texture successScreen;
    // Used to place non-static elements on top of the static art textures.
    Location countdownLocation = Location { 50, 11 };
    Location levelnumberLocation = Location { 35, 11 };
    Location failLevelnumberLocation = Location { 45, 10 };

private:
    void setupTextures();
    bool KeyUp(Keytype k);
    void spawnEntities();
    void spawnRandomEnemy(Entity* p, Location exitloc);



public:
    ARLG(int level, bool enhanced);
    ~ARLG() {}

    void update() override;
    void draw(View &v) override;
    void onStart() override;
    void onStop() override;

    Location getRandomLocation();
    void enemyDespawning(EntityType type, Location l);
    void spawnPlayerProjectile(Location l, Direction d);
    void spawnEnemyProjectile(Location l, Direction d);
    void spawnBossEnemy(Location l, int stage);
    void completedLevel();
    int getNumberofEnemies();
    void lost();
    void won();
};
}

#endif
