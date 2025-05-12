#ifndef PIECE_H
#define PIECE_H
#include "../engine/entity.h"
#include "keytype.h"

namespace age {

enum PieceType {None = 0, I = 1, O = 2, J = 3, L = 4, T = 5, S = 6, Z = 7};


class Piece : public Entity {
    PieceType type;
    int rotation;
    int lastRotation = 0;
public:
    bool rotationEnabled = true;
    using Entity::shouldDespawn;

public:
    Piece(PieceType type, int rotation, Location location);
    const Texture getSprite() const;
    PieceType getType() const;
    static string PieceTypeToString(PieceType p);

private:
    string doubleString(const string &s) const;
    void doUpdate(Action a, Action prev, long numTicks) override;
    void doDraw(View &v) override;
    void doCollidingWith(const Entity &other, Location before, Location after) override;

};


}


#endif
