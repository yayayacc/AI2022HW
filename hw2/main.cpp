# include<iostream>
# include"classes.h"
# include"fun.cpp"
using namespace std;
int x_whitespace = 0;
int main()
{
    State p(0);
    p.init();
    State* res = p.search();
    if(res){
        cout<<res->cells[0][0];
    }
    // path_trace(res);
    //system("pause");
    return 0;
}