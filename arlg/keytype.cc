#include "keytype.h"
namespace age {

bool KeyDown(Action a, Keytype k) {
    switch (k)
    {
    case Keytype::DOWN: return a == KEY_DOWN; break;
    case Keytype::UP: return a == KEY_UP; break;
    case Keytype::LEFT: return a == KEY_LEFT; break;
    case Keytype::RIGHT: return a == KEY_RIGHT; break;
    case Keytype::SHOOTDOWN: return a == 's'; break;
    case Keytype::SHOOTUP: return a == 'w'; break;
    case Keytype::SHOOTLEFT: return a == 'a'; break;
    case Keytype::SHOOTRIGHT: return a == 'd'; break;
    
    default: return false; break;
    }
}
}
