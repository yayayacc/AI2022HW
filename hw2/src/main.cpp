// #include <test.h>
// #include <test_output.h>

// int main() {
//     // test();
//     //   test_stream();

//     // createObjectJson();

//     //   auto json = createObjectJson();
//     //   std::cout << json << std::endl;
// }

#include "classes.h"
#include <iostream>

using namespace std;

int x_whitespace = 0;

int main() {
    State p(0);
    p.init();

    State* res = p.search();

    if (res) {
        cout << res->cells[0][0];
    }
    else{
        cout<<11;
    }

    // path_trace(res);
    // system("pause");
    return 0;
}
