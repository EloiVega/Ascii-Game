#include "EventMaker.h"
using namespace std;

int main(){
    start:;
    EventMaker EM;
    while(1){
        int num = EM.MakeMove();
        if(!num)    break;
        if(num == 2){
            system("cls");
            goto start;
        }
    }

    return 0;
}
