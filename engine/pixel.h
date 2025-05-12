#ifndef PIXEL_H
#define PIXEL_H
#include <ncurses.h>
#include "location.h"
namespace age {

struct Pixel {
    Location location;
    char character;
    int cursesColourPair;

    Pixel(): location{ Location{0,0}}, character{' '}, cursesColourPair{DEFAULTCOLOUR} {}
    Pixel(int x, int y, char c): location{ Location{x,y}}, character{c}, cursesColourPair{DEFAULTCOLOUR} {}
    Pixel(Location l, char c): location{l}, character{c}, cursesColourPair{DEFAULTCOLOUR} {}
    Pixel(int x, int y, char c, int colourPair): location{ Location{x,y}}, character{c}, cursesColourPair{colourPair} {}
    Pixel(Location l, char c, int colourPair): location{l}, character{c}, cursesColourPair{colourPair} {}
    ~Pixel() {}
};
}

#endif
