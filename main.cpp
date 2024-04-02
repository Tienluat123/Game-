#include "Normal.h"
#include "Hard.h"
#include "PvP.h"

int main (){
    initWindow(1500, 500);

    int status;
    Player p, p1, p2;

    while ((status = menu()) != 4){
        switch (status)
        {
        case 0:
            getPlayerInfor(p);
            normalMode(p);
            break;
        case 1:
            getPlayerInfor(p);
            hardMode(p);
            break;
        case 2: 
            char c;
            printLeaderBoard(c);
            break;
        case 3:
            getPlayerInfor(p1);
            system("cls");
            getPlayerInfor(p2);
            pvpMode(p1, p2);
            break;
        default:
            break;
        }
    }
}