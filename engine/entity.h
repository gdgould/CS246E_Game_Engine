#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
using std::vector;
#include <memory>
using std::unique_ptr;
#include "texture.h"
#include "view.h"
#include "movementAction.h"

namespace age {

class Entity {
    private:
        vector<unique_ptr<MovementAction>> movements;
        int ticksOffscreen;
        Location prevLocation;
    protected:
        Texture texture;
        bool shouldDespawn = false;
    public:
        bool visible, enabled;
        double height;
        Location location;
        int ticksToDespawn = 10;

    public:
        Entity();
        virtual ~Entity() = default;

        void addMovementAction(unique_ptr<MovementAction> m);
        void clearMovementActions();
        vector<Location> getNextMoves(Action a, long numTicks);
        Location getPrevLocation() const;
        void setTexture(Texture t);
        bool intersectsWith(Location point);
        bool intersectsWith(const Entity &point);

        void Move(Action a, long numTicks);
        void Update(Action a, Action prev, long numTicks);
        void Draw(View &v);
        void OtherColliding(const Entity &other, Location before, Location after); // Another entity is colliding with me
        void CollidingWith(const Entity &other, Location mybefore, Location myafter); // I am colliding with another entity
        
        bool IsDespawning() const;

    private:
        virtual void doUpdate(Action a, Action prev, long numTicks);
        virtual void doDraw(View &v);
        virtual void doOtherColliding(const Entity &other, Location before, Location after);
        virtual void doCollidingWith(const Entity &other, Location mybefore, Location myafter);
        virtual bool doIsDespawning() const;
};
}

#endif
