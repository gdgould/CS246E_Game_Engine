#include "location.h"
#include <cmath>
namespace age {

Location::Location(): x{0}, y{0} {}
Location::Location(int x, int y): x{x}, y{y} {}
Location::~Location() {}

bool Location::operator==(const Location &other) const {
    return (this->x == other.x && this->y == other.y);
}
bool Location::operator!=(const Location &other) const {
    return !(*this == other);
}

Location Location::operator+(const Location &other) const {
    return Location {this->x + other.x, this->y + other.y};
}
Location Location::operator-(const Location &other) const {
    return Location {this->x - other.x, this->y - other.y};
}

double Location::distance(const Location &other) const {
    return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
}

}
