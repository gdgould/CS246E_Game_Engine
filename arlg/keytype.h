#ifndef KEYTYPE_H
#define KEYTYPE_H
#include <ncurses.h>
#include "../engine/action.h"
namespace age {
enum Keytype { LEFT, RIGHT, UP, DOWN, SHOOTLEFT, SHOOTRIGHT, SHOOTUP, SHOOTDOWN };

bool KeyDown(Action a, Keytype k);
}

#endif
