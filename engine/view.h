#ifndef VIEW_H
#define VIEW_H
#include "location.h"
#include "constants.h"
#include <string>
namespace age {

class View { 
public:
    virtual ~View() = default;
    virtual void update(Location location, char character, double height) = 0;
    void update(Location location, std::string s, double height, int cursesColourPair = DEFAULTCOLOUR) {
        for (size_t i = 0; i < s.size(); i++)
        {
            update(location + Location{(int)i, 0}, s[i], height, cursesColourPair);
        }
    }
    virtual void update(Location location, char character, double height, int cursesColourPair) {
        update(location, character, height);
    }
    virtual void updateStatusOne(std::string s) = 0;
    virtual void updateStatusTwo(std::string s) = 0;
    virtual void updateStatusThree(std::string s) = 0;
    virtual void displayView() = 0;
    virtual void clearView() {}
};
}

#endif


