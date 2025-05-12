#ifndef __CURSE_KEYBOARD___H__
#define __CURSE_KEYBOARD___H__

#include "controller.h"
#include "action.h"
#include <iostream>
#include <string>
#include <map>
#include <ncurses.h>
namespace age {
class CursesKeyboard: public Controller {

    Action action() override;
public:
    CursesKeyboard();
    ~CursesKeyboard();
};
}
#endif
