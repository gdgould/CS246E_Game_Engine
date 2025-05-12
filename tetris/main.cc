#include <cstdlib>
#include <iostream>
#include "tetris.h"
using namespace age;

int main(int argc, char* argv[]) {
    // This option for Demo purposes
    int inputSmoothing = 2;
    for (size_t i = 1; i < argc; i++)
    {
        if (std::string(argv[i]).substr(0, 9) == "--smooth=") {
            if (std::string(argv[i]).length() == 10) {
                inputSmoothing = argv[i][9] - '0';
            }
        }
    }

    Tetris g {};
    g.setInputSmoothing(inputSmoothing);
    g.run();
    
    return 0;
}
