#include "Normal.h"
#include "Hard.h"
#include "PvP.h"
#include "Hidden.h"

int main (){
    initWindow(2000, 500);

    int status;
    Player p, p1, p2;

    while ((status = menu()) != 5){
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
        case 4:
            getPlayerInfor(p);
            system("cls");
            hiddenMode(p);
            break;
        default:
            break;
        }
    }
}