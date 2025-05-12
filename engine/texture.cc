#include "texture.h"
namespace age {

Texture::Texture(): pixels{vector<Pixel>{}} {}
Texture::Texture(int width, int height, char character, const Location &l, int cursesColourPair) {
    for (int i = l.x; i < l.x + width; i++) {
        for (int j = l.y; j < l.y + height; j++) {
            pixels.push_back(Pixel {i, j, character, cursesColourPair});
        }
    }
}
Texture::Texture(const string &s, const Location &l, const string &transparencyChars, int cursesColourPair) {
    int xPos = 0;
    int yPos = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\n') { ++yPos; xPos = 0; }
        else {
            if (transparencyChars.find(s[i]) == string::npos) {
                pixels.push_back(Pixel {xPos + l.x, yPos + l.y, s[i], cursesColourPair});
            }
            ++xPos;
        }
    }
}

Texture::Texture(const Texture& other) {
    pixels = vector<Pixel>{};
    pixels.reserve(other.pixels.size());
    for (size_t i = 0; i < other.pixels.size(); i++)
    {
        pixels.push_back(other.pixels[i]);
    }
}
Texture::Texture(Texture&& other) {
    pixels = other.pixels;
    other.pixels = vector<Pixel>{};
}
Texture::Texture(vector<Texture> other) {
    pixels = vector<Pixel>{};
    for (size_t i = 0; i < other.size(); i++) {
        for (size_t j = 0; j < other[i].pixels.size(); j++) {
            // Check for duplication
            for (size_t k = 0; k < pixels.size(); k++)
            {
                if (pixels[k].location == other[i].pixels[j].location) { goto end; }
            }
            pixels.push_back(other[i].pixels[j]);
            end:;
        }
    }    
}


Texture &Texture::operator=(Texture other) {
    std::swap(pixels, other.pixels);
    return *this;
}

Texture::~Texture() {}

void Texture::drawAt(View &v, Location l, double height) {  
    for (auto &p : pixels)
    {
        v.update(p.location + l, p.character, height, p.cursesColourPair);
    }
}

bool Texture::intersectsWith(const Location &l) {
    for (auto &p : pixels) {
        if (p.location == l) { return true; }
    }
    return false;
}
}
