#include "game.h"
#include <thread>
#include <ratio>
#include <iostream>
namespace age {

Game::Game(): views{vector<unique_ptr<View>>{}}, control{nullptr}, entities{vector<unique_ptr<Entity>>{}} {
    border = make_unique<Entity>();
    border->height = 1;
    string top = "+------------------------------------------------------------------------------+";
    string side = "|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n";
    border->setTexture(vector<Texture> {Texture(top, Location{LEFTBORDER,TOPBORDER}), Texture(top, Location{LEFTBORDER,BOTTOMBORDER}),
                                        Texture(side, Location{LEFTBORDER,TOPBORDER + 1}), Texture(side, Location{RIGHTBORDER, TOPBORDER + 1})});
}

void Game::AddView(unique_ptr<View> v) {
    views.emplace_back(std::move(v));
}

void Game::AddController(unique_ptr<Controller> c) {
    control = std::move(c);
}

Action Game::getAction() {
    return cacheAction;
}
Action Game::getPrevAction() {
    return prevAction;
}
void Game::updateInternalActions() {
    prevAction = cacheAction;
    Action a = (control ? control->getAction() : (Action)(-1));
    if (a == (Action)(-1)) {
        if (cachedFrames > 0) { --cachedFrames; }
        else { cacheAction = (Action)(-1); }
    }
    else {
        cacheAction = a;
        cachedFrames = inputSmoothing;
    }
}

void Game::AddEntity(unique_ptr<Entity> e) {
    entities.emplace_back(std::move(e));
}
void Game::ClearEntities() {
    clearEntitiesNextTick = true;    
}

// The loop that runs the game
void Game::run() {
    onStart();
    running = true;
    while(running) {
        auto startTime = std::chrono::steady_clock::now();
        tick();
        ++elapsedTicks;
        auto stopTime = std::chrono::steady_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(startTime - stopTime);
        if (elapsed > frameElapsedTime) {
            runningSlow = true;
        }
        else {
            runningSlow = false;
            std::this_thread::sleep_for(frameElapsedTime - elapsed);
        }
    }
    onStop();
}

void Game::tick() {
    updateInternalActions();
        //statusLineThree = std::to_string(entities.size());

    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->Update(cacheAction, prevAction, elapsedTicks);

        if (collisionType == Game::CollisionType::Iterative && entities[i]->enabled) {
        // In the iterative collision type, entities handled by the game engine have their moves processed manually, not through Move
        // This is so we can call collisions between each move, and the entities can reflect that

            vector<Location> moves = entities[i]->getNextMoves(cacheAction, elapsedTicks);
            // We run through each move to see which cause collisions
            for (size_t j = 1; j < moves.size(); j++) {
                entities[i]->location = entities[i]->location + (moves[j] - moves[j - 1]); // Shift the entity by the correct amount
                for (size_t k = 0; k < entities.size(); k++) {
                    if (entities[i].get() != entities[k].get() && entities[i]->height == entities[k]->height && entities[i]->intersectsWith(*entities[k])) {
                        entities[i]->CollidingWith(*entities[k], moves[j - 1], moves[j]); 
                        entities[k]->OtherColliding(*entities[i], moves[j - 1], moves[j]); 
                    }
                }
                if (borderCollide && entities[i]->intersectsWith(*border)) {
                    entities[i]->CollidingWith(*border, moves[j - 1], moves[j]); 
                }
            }
        }
        else {
            entities[i]->Move(cacheAction, elapsedTicks);
        }
    }

    if (collisionType == Game::CollisionType::Normal) {
        for (size_t i = 0; i < entities.size(); i++) {
            for (size_t j = i + 1; j < entities.size(); j++) {
                if (entities[i].get() != entities[j].get() && entities[i]->height == entities[j]->height && entities[i]->intersectsWith(*entities[j])) {
                    entities[i]->OtherColliding(*entities[j], entities[j]->getPrevLocation(), entities[j]->location); 
                    entities[j]->OtherColliding(*entities[i], entities[i]->getPrevLocation(), entities[i]->location); 
                }
            }
            if (borderCollide && entities[i]->intersectsWith(*border)) {
                entities[i]->OtherColliding(*border, Location{0,0}, Location{0,0});
            }
        }
    }

    update();

    // Despawn entities as requested.
    for (int i = entities.size() - 1; i >= 0; i--)
    {
        if (clearEntitiesNextTick || entities[i]->IsDespawning()) {

            entities.erase(entities.begin() + i);
        }
    }
    clearEntitiesNextTick = false;

    for (auto &v : views) {
        v->clearView();
        for (auto &e : entities) {
            e->Draw(*v);
        }
        border->Draw(*v);
        draw(*(v.get()));
        v->updateStatusOne(statusLineOne);
        v->updateStatusTwo(statusLineTwo);
        v->updateStatusThree(statusLineThree);
        v->displayView();
    }
}

void Game::stop() { running = false; }

void Game::setEntityEnableState(bool enabled) {
    for (auto &e : entities) {
        e->enabled = enabled;
    }
}
void Game::setEntityVisibleState(bool visible) {
    for (auto &e : entities) {
        e->visible = visible;
    }
}


long Game::getElapsedTicks() { return elapsedTicks; }
void Game::resetElapsedTicks() { elapsedTicks = 0; }
void Game::toggleEnhancements(bool enhanced) {
    enhancementsOn = enhanced;
    if (enhanced) {
        frameElapsedTime = userDesiredFrameTime;
    }
    else {
        frameElapsedTime = defaultFrameTime;
    }
}
const bool &Game::runningEnhanced() { return enhancementsOn; }


int64_t Game::framerateToFrametime(int64_t rate) {
    // (clock ticks / second) / (clock ticks / frame) = frames / second
    // Also works the other way!
    // (clock ticks / second) / (frames / second) = clock ticks / frame
    return (std::chrono::microseconds::period::den / std::chrono::microseconds::period::num) / rate;
}

uint Game::getFramerate() {
    return framerateToFrametime(frameElapsedTime.count());
}
void Game::setFramerate(int framerate) {
    userDesiredFrameTime = std::chrono::microseconds(framerateToFrametime(framerate));
}
void Game::setInputSmoothing(int iSmooth) {
    if (iSmooth < 0) { iSmooth = 0; }
    inputSmoothing = iSmooth;
}
bool Game::isRunningSlow() { return runningSlow; }
    
}
