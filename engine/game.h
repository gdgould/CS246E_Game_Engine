#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include <string>
#include <chrono>
using std::vector;
using std::unique_ptr;
using std::make_unique;
#include "entity.h"
#include "controller.h"
#include "moveline.h"
#include "moveToBorder.h"
#include "movePlayerControlled.h"
class View;
namespace age {

class Game {
public:
/// Iterative -- collisions are checked after each move of each entity.
///              An entity's collision methods may be called multiply times per pair of entities.
/// Normal -- all entities are moved, then collisions are checked between entities.
///           An entity's collision method will be called at most once per pair of entities.
enum CollisionType { Iterative, Normal };

private:
    vector<unique_ptr<View>> views;
    unique_ptr<Controller> control;
    unique_ptr<Entity> border;
    Action cacheAction;
    Action prevAction;
    int cachedFrames;
    long elapsedTicks = 0;
    int inputSmoothing = 2; // Determines how long an input should be sustained after its key is released.
                            // 0 represents no sustain (raw input)
    std::chrono::microseconds defaultFrameTime = std::chrono::microseconds(50000L);
    std::chrono::microseconds userDesiredFrameTime = defaultFrameTime;
    std::chrono::microseconds frameElapsedTime = defaultFrameTime;
    bool running = false;
    bool runningSlow = false;
    bool enhancementsOn = false;
    bool clearEntitiesNextTick = false;
protected:
    vector<unique_ptr<Entity>> entities;
public:
    Game::CollisionType collisionType = Game::CollisionType::Normal;
    bool borderCollide = false;
    std::string statusLineOne = "";
    std::string statusLineTwo = "";
    std::string statusLineThree = "";

    Game();
    virtual ~Game() = default;

protected:
    void AddView(unique_ptr<View> v);
    void AddController(unique_ptr<Controller> c);
    Action getAction();
    Action getPrevAction();
    void AddEntity(unique_ptr<Entity> e);
    void ClearEntities();

private:
    void updateInternalActions();
    virtual void update() = 0;
    virtual void draw(View &v) = 0;
    virtual void onStart() {}
    virtual void onStop() {}
    int64_t framerateToFrametime(int64_t rate);

public:
    void run();
    void tick();
    void stop();
    void setEntityEnableState(bool enabled);
    void setEntityVisibleState(bool visible); 

    long getElapsedTicks();
    void resetElapsedTicks();
    void toggleEnhancements(bool enhanced);
    const bool &runningEnhanced();
    uint getFramerate();
    void setFramerate(int framerate);
    void setInputSmoothing(int iSmooth);
    bool isRunningSlow();
};

}

#endif
