#include "profiler.h"
#include "state.h"

int main() {
    {

        PROFILE_SCOPE("Search");

        std::cout<<"请问您选择什么方式来进行九宫格重排？（1带表广度优先，2代表深度优先）"<<std::endl;
        char a;
        std::cin>>a;

        
        State p(0);
        //p.test();
        p.init();

        

        if(int(a) == 49){
            State* res = p.search_width_first();
        }
            
        else if (int(a) == 50){
            State* res = p.search_depth_first();
        }
        else{
            std::cout<<"输入错误，请重新启动程序"<<std::endl;
        }
        // std::cout << ((res) ? res->cells[0][0] : 11) << std::endl;
    }

    PROFILE_DISPLAY();

    return 0;
}