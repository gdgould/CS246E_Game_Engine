#ifndef TEXTURE_H
#define TEXTURE_H
#include <vector>
using std::vector;
#include <string>
using std::string;
#include "location.h"
#include "constants.h"
#include "pixel.h"
#include "view.h"

namespace age {

class Texture {
public:
    std::vector<Pixel> pixels;

    Texture();
    Texture(int width, int height, char character, const Location &l = Location{0,0}, int cursesColourPair = DEFAULTCOLOUR);
    Texture(const string &s, const Location &l = Location{0,0}, const string &transparencyChars = "", int cursesColourPair = DEFAULTCOLOUR);


    Texture(const Texture& other);
    Texture(Texture&& other);
    Texture(const vector<Texture> other);

    Texture &operator=(Texture other);

    ~Texture();

    void drawAt(View &v, Location l, double height);
    bool intersectsWith(const Location &l);
};
}

#endif
