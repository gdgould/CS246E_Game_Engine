#include "cursescontrol.h"
#include <string>
namespace age {

CursesKeyboard::CursesKeyboard() {
    setlocale(LC_ALL, "");
    timeout(0);
}
CursesKeyboard::~CursesKeyboard() {}

Action CursesKeyboard::action(){
    return (Action)getch();
}

}
