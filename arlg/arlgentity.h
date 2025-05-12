#ifndef ARLGENTITY_H
#define ARLGENTITY_H
#include "../engine/entity.h"
#include "arlg.h"
namespace age {


class ARLGEntity : public Entity {
private:
    EntityType type;
    int invincibleCounter = 0;
protected:
    bool hasHealth = true;
    ARLG &game;
    int health;

private:
    bool doIsDespawning() const override;

protected:
    void goInvincible();
    void updateInvincible();

public:
    ARLGEntity(ARLG& game, int health, EntityType type, Location l);
    virtual ~ARLGEntity() override;

    int getHealth() const;
    bool getHasHealth() const;
    bool isInvincible() const;
    EntityType getType() const;
};



}

#endif
