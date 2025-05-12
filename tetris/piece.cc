#include "piece.h"

namespace age {

Piece::Piece(PieceType type, int rotation, Location location): Entity(), type{type}, rotation{rotation} {
    this->location = location;
    setTexture(getSprite());
}

// duplicates all non-newline characters
string Piece::doubleString(const string& s) const {
    string out = "";
    for (size_t i = 0; i < s.size(); i++) {
        out += s[i];
        if (s[i] != '\n') { out += s[i]; }
    }
    return out;
}

const Texture Piece::getSprite() const {
    vector<vector<string>> textures = vector<vector<string>> {
        vector<string> {}, // since the enum is one-indexed
        vector<string> {"    \n    \nIIII\n    ", "  I \n  I \n  I \n  I "},
        vector<string> {"    \n OO \n OO \n    "},
        vector<string> {"   \nJJJ\n  J", " J \n J \nJJ ", "J  \nJJJ\n   ", " JJ\n J \n J "},
        vector<string> {"   \nLLL\nL  ", "LL \n L \n L ", "  L\nLLL\n   ", " L \n L \n LL"},
        vector<string> {"   \nTTT\n T ", " T \nTT \n T ", " T \nTTT\n   ", " T \n TT\n T "},
        vector<string> {"   \n SS\nSS ", " S \n SS\n  S"},
        vector<string> {"   \nZZ \n ZZ", "  Z\n ZZ\n Z "}
    };  
    // We can use the piece type as the colour since we defined the colours pairs this way in tetris.cc
    return Texture(doubleString(textures[type][rotation % textures[type].size()]), Location{0,-2}, " ", (int)type);
}

PieceType Piece::getType() const { return type; }
string Piece::PieceTypeToString(PieceType p) {
    switch (p) {
        case PieceType::I: return "I";
        case PieceType::O: return "O";
        case PieceType::J: return "J";
        case PieceType::L: return "L";
        case PieceType::T: return "T";
        case PieceType::S: return "S";
        case PieceType::Z: return "Z";
        case PieceType::None: return "";
    }
    return "";
}

void Piece::doUpdate(Action a, Action prev, long numTicks) {
    if (rotationEnabled && KeyDown(a, Keytype::A) && !KeyDown(prev, Keytype::A)) {
        ++lastRotation;
        ++rotation;
        setTexture(getSprite());
    }
    else if (rotationEnabled && KeyDown(a, Keytype::B) && !KeyDown(prev, Keytype::B)) {
        --lastRotation;
        --rotation;
        setTexture(getSprite());
    }
    else {
        lastRotation = 0;
    }
}
void Piece::doDraw(View &v) {

}
void Piece::doCollidingWith(const Entity &other, Location mybefore, Location myafter) {
    if (mybefore.y != myafter.y) { shouldDespawn = true; } // We have hit something from above
    if (lastRotation) { rotation -= lastRotation; setTexture(getSprite()); } // We have rotated into something
    location = mybefore;
}

}
