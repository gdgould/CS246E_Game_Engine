#include "arlgentity.h"
namespace age {

ARLGEntity::ARLGEntity(ARLG &game, int health, EntityType type, Location l): Entity(), type{type}, game{game}, health{health} {
    this->height = 0;
    this->location = l;
}
ARLGEntity::~ARLGEntity() {}

void ARLGEntity::goInvincible() { invincibleCounter = IFRAMES; }
void ARLGEntity::updateInvincible() {
    if (invincibleCounter > 0) { --invincibleCounter; this->visible = (invincibleCounter / 2) % 2 == 0; } 
    else if (invincibleCounter < 0) { invincibleCounter = 0; this->visible = true; }
}

int ARLGEntity::getHealth() const { return hasHealth ? health : -1; }
bool ARLGEntity::getHasHealth() const { return hasHealth; }
bool ARLGEntity::isInvincible() const { return invincibleCounter > 0; }
EntityType ARLGEntity::getType() const { return type; }

bool ARLGEntity::doIsDespawning() const { return hasHealth && health == 0; }

}
