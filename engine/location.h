#ifndef LOCATION_H
#define LOCATION_H
namespace age {

struct Location {
    int x, y;

    Location ();
    Location(int x, int y);
    ~Location();
    bool operator==(const Location &other) const;
    bool operator!=(const Location &other) const;
    Location operator+(const Location &other) const;
    Location operator-(const Location &other) const;

    double distance(const Location &other) const;
};
}

#endif
