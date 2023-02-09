#include "profiler.h"
#include "state.h"

int main() {
    {
        PROFILE_SCOPE("Search");

        State p(0);
        p.init();

        State* res = p.search();
        std::cout << ((res) ? res->cells[0][0] : 11) << std::endl;
    }

    PROFILE_DISPLAY();

    return 0;
}
