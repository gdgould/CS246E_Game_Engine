#ifndef KEYTYPE_H
#define KEYTYPE_H
#include <ncurses.h>
namespace age {
    enum Keytype { LEFT, RIGHT, UP, DOWN, A, B, START, SELECT, TOGGLEENHANCEMENTS};

static bool KeyDown(Action a, Keytype k) {
    switch (k)
    {
    case Keytype::A: return a == 'x' || a == 'l'; break;
    case Keytype::B: return a == 'z' || a == 'k'; break;
    case Keytype::DOWN: return a == 's' || a == KEY_DOWN; break;
    case Keytype::UP: return a == 'w' || a == KEY_UP; break;
    case Keytype::LEFT: return a == 'a' || a == KEY_LEFT; break;
    case Keytype::RIGHT: return a == 'd' || a == KEY_RIGHT; break;
    case Keytype::START: return a == ' '; break;
    case Keytype::SELECT: return a == 'b'; break;
    case Keytype::TOGGLEENHANCEMENTS: return a == 'e'; break;
    
    default: return false; break;
    }
}
}

#endif
