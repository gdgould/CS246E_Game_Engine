#ifndef CURSESVIEW_H
#define CURSESVIEW_H
#include <vector>
#include <string>
using std::string;
using std::vector;
#include "view.h"
#include "constants.h"

namespace age {
class CursesView: public View {
    const bool &runningEnhanced;
    vector<vector<double>> heights;

    void resetHeights();
public:
    CursesView(const bool &runningEnhanced);
    ~CursesView();
    void update(Location location, char character, double height) override;
    void update(Location location, char character, double height, int cursesColourPair) override;
    void updateStatusOne(string s) override;
    void updateStatusTwo(string s) override;
    void updateStatusThree(string s) override;

    void displayView() override;
    void clearView() override;
};

}
#endif
