#include <cstdlib>
#include <cstring>
#include "arlg.h"
using namespace age;

int main(int argc, char* argv[]) {
    bool enhanced = true;
    int startLevel = 1;
    for (size_t i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "--enhancements=Off") {
            enhanced = false;
        }
        else if (std::string(argv[i]) == "--enhancements=On") {
            enhanced = true;
        }
        else if (strlen(argv[i]) == 1 && argv[i][0] >= '1' && argv[i][0] <= '6') {
            startLevel = argv[i][0] - '0';
        }
    }

    ARLG g { startLevel, enhanced };
    g.run();

    return 0;
}
