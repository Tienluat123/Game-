#include "Normal.h"

int main (){
    initWindow(1000, 500);

    int status;
    Player p;

    while ((status = menu()) != 3){
        switch (status)
        {
        case 0:
            getPlayerInfor(p);
            normalMode(p);
            break;
        case 1:
            break;
        case 2: 
            char c;
            printLeaderBoard(c);
            break;
        default:
            break;
        }
    }
}