#include "entity.h"
#include "constants.h"
#include "movePlayerControlled.h" // So that we can do bounds checking
#include <iostream>
namespace age {

Entity::Entity(): movements{vector<unique_ptr<MovementAction>>()}, ticksOffscreen{0}, texture{Texture()},
                    visible{true}, enabled{true}, height{0.0}, location{ Location{0,0} } {}

void Entity::addMovementAction(unique_ptr<MovementAction> m) {
    movements.emplace_back(std::move(m));
}
void Entity::clearMovementActions() {
    movements.clear();
}

// Returns a list of the moves that the entity would make by applying its movement patterns one by one.
// The first move is always the current position
vector<Location> Entity::getNextMoves(Action a, long numTicks) {
    vector<Location> out {location};
    Location newLoc = location;
    for (auto &m : movements) {
        MovePlayerControlled *p = dynamic_cast<MovePlayerControlled*>(m.get());
        if (p) { newLoc = p->nextMove(newLoc, a, numTicks); }
        else { newLoc = m->nextMove(newLoc, numTicks); }
        out.push_back(newLoc);
    }
    return out;
}
Location Entity::getPrevLocation() const { return prevLocation; }
void Entity::setTexture(Texture t) { texture = t; }
bool Entity::intersectsWith(Location l) { return texture.intersectsWith(l - this->location); }


bool Entity::intersectsWith(const Entity &other) {
    for (auto &point : other.texture.pixels)
    {
        if (this->intersectsWith(point.location + other.location)) { return true; }
    }
    return false;
}

void Entity::Move(Action a, long numticks) {
    if (!enabled) { return; }
    prevLocation = location;
    vector<Location> moves = getNextMoves(a, numticks);
    location = moves[moves.size() - 1]; 
}

void Entity::Update(Action a, Action prev, long numticks) {
    if (!enabled) { return; }
    doUpdate(a, prev, numticks);

    // Check to see if we must enforce bounds checking
    for (auto &m : movements) {
        if (dynamic_cast<MovePlayerControlled*>(m.get())) {
            if (location.x <= LEFTBORDER) { location.x = LEFTBORDER + 1; }
            else if (location.x >= RIGHTBORDER) { location.x = RIGHTBORDER - 1; }
            if (location.y <= TOPBORDER) { location.y = TOPBORDER + 1; }
            else if (location.y >= BOTTOMBORDER) { location.y = BOTTOMBORDER - 1; }
            return;
        }
    }

    if (location.x < LEFTBORDER || location.x > RIGHTBORDER ||
        location.y < TOPBORDER || location.y > BOTTOMBORDER) {
            ++ticksOffscreen;
    }
    else { ticksOffscreen = 0; }
}

void Entity::Draw(View &v) {
    if (!visible) { return; }
    doDraw(v);
    texture.drawAt(v, this->location, this->height);
}

void Entity::OtherColliding(const Entity &other, Location before, Location after) {
    if (!enabled) { return; }
    doOtherColliding(other, before, after);
}
void Entity::CollidingWith(const Entity &other, Location mybefore, Location myafter) {
    if (!enabled) { return; }
    doCollidingWith(other, mybefore, myafter);
}


bool Entity::IsDespawning() const {
    return shouldDespawn || ticksOffscreen >= ticksToDespawn || doIsDespawning();
}

void Entity::doUpdate(Action a, Action prev, long numTicks) {}
void Entity::doDraw(View &v) {}
void Entity::doOtherColliding(const Entity &other, Location before, Location after) {}
void Entity::doCollidingWith(const Entity &other, Location mybefore, Location myafter) {}
bool Entity::doIsDespawning() const { return false; }

    
}
