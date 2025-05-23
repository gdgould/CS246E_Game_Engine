#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "action.h"
#include <string>

class Controller{
    virtual Action action() = 0;
public:
    Action getAction();
    virtual ~Controller() = default;
};
#endif
