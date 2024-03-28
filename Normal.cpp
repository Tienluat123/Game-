#include "Normal.h"
#include <iostream>
using namespace std;

char bg[20][41];

//initialize the board for normal mode
void initBoard(Cell_1** a){
    //dynamic allocate the board and asign the coord for each box
    for (int i = 0; i < BOARDHEIGHT; i++){
        a[i] = new Cell_1[BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++){
            a[i][j].i = i;
            a[i][j].j = j;
        }
    }

    //assign a character for each box in the board
    int count = (BOARDWIDTH * BOARDHEIGHT) / 2;
    while (count){
        //the index and the time that character appears
        int idx, time = 2;
        //random to get the character
        char ch = 65 + rand() % 26;
        //assign the character into the board
        while (time){
            //get random index in the board
            idx = rand() % 40;
            //check if that index already had a character or not
            if (a[idx / 8][idx % 8].c == ' '){
                a[idx / 8][idx % 8].c = ch;
                time--;
            }
        }
        count--;
    }
}

//delete the board when game is over
void deleteBoard(Cell_1** a){
    for (int i = 0; i < BOARDHEIGHT; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            if (a[i][j].valid){
                a[i][j].deleteBox();
                if (j < 4)
                    displayNormalBg(bg, j, i);
                
                Sleep(100);
            }
        }
    }
    for (int i = 0; i < BOARDHEIGHT; i++){
        delete[] a[i];
    }
    delete[] a;
}

//delete the board when the player lose the stages
// void deleteBoardWhenLose(Cell_1** a){
//     //find the valid boxes that have not been deleted
   
    
//     deleteBoard(a);
// }

void renderBoard (Cell_1** a){
    for (int i = 0; i < BOARDHEIGHT; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            a[i][j].drawBox(112);
        }
    }
}

//move
void move (Cell_1** a, Position& pos, int& status, Player& p, Position select_pos[], int& pair){
    int temp, key;
    temp = _getch();

    //if the pressed key is not arrow key
    if (temp && temp != 224){
        if (temp == ESC_KEY){
            status = 2;
        } else if (temp == ENTER_KEY){
            //check if the pair is wrong
            if (pos.x == select_pos[0].x && pos.y == select_pos[0].y){
                a[select_pos[0].y][select_pos[0].x].drawBox(70);
                Sleep(500);

                a[select_pos[0].y][select_pos[0].x].selected = 0;
                pair = 2;
                select_pos[0] = {-1, -1};
                p.life--;

                goToXY(70, 0);
                cout << "Life: " << p.life;
            } else {
                select_pos[2 - pair].x = pos.x;
                select_pos[2 - pair].y = pos.y;
                a[pos.y][pos.x].selected = 1;
                pair--;

                //if the player have been chosen pair
                if (pair == 0){
                    if (a[select_pos[0].y][select_pos[0].x].c == a[select_pos[1].y][select_pos[1].y].c){
                        if (allcheck(a, select_pos[0].y, select_pos[0].x, select_pos[1].y, select_pos[1].x)){
                            p.point += 10;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            a[select_pos[0].y][select_pos[0].x].drawBox(40);
                            a[select_pos[1].y][select_pos[1].x].drawBox(40);
                            Sleep(500);

                            a[select_pos[0].y][select_pos[0].x].valid = 0;
                            a[select_pos[0].y][select_pos[0].x].deleteBox();
                            if (select_pos[0].x < 4)
                                displayNormalBg(bg, select_pos[0].x, select_pos[0].y);
                            a[select_pos[1].y][select_pos[1].x].valid = 0;
                            a[select_pos[1].y][select_pos[1].x].deleteBox();
                            if (select_pos[1].x < 4)
                                displayNormalBg(bg, select_pos[1].x, select_pos[1].y); 
                        } else {
                            a[select_pos[0].y][select_pos[0].x].drawBox(70);
                            a[select_pos[1].y][select_pos[1].x].drawBox(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    } else {
                        a[select_pos[0].y][select_pos[0].x].drawBox(70);
                        a[select_pos[1].y][select_pos[1].x].drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }

                    //return the
                    a[select_pos[0].y][select_pos[0].x].selected = 0;
                    a[select_pos[1].y][select_pos[1].x].selected = 0;
                    pair = 2;
                    select_pos[0] = {-1, -1};
                    select_pos[1] = {-1, -1};

                    for (int i = pos.y; i < BOARDHEIGHT; i++){
                        for (int j = pos.x; i < BOARDWIDTH; j++){
                            if (a[i][j].valid){
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++){
                        for (int j = 0; j <= pos.x; j++){
                            if (a[i][j].valid){
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }

    // if the pressed key is arrow key  
    } else {
        //movement
        //check if the box is chosen or not
        if ((pos.y != select_pos[0].y || pos.x != select_pos[0].x) && (pos.y != select_pos[1].y || pos.x != select_pos[1].x))
        {
            a[pos.y][pos.x].selected = 0;
        }
        //move the chosen box by pressing arrow keys
        switch(key = _getch()){
            case KEY_UP:
                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y - 1; j >= 0; j--) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i >= 0; i--) {
                    for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                break;
            case KEY_DOWN:
                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x; i < BOARDWIDTH; i++) {
                    for (int j = 0; j < pos.y; j++) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }

                for (int i = pos.x - 1; i >= 0; i--) {
                    for (int j = 0; j < pos.y; j++) {
                        if (a[j][i].valid) {
                            pos.x = i;
                            pos.y = j;
                            return;
                        }
                    }
                }
                break;
            case KEY_LEFT:
                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x - 1; j >= 0; j--) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }
                break;
            case KEY_RIGHT:
                for (int i = pos.y; i >= 0; i--) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y; i >= 0; i--) {
                    for (int j = 0; j < pos.x; j++) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }

                for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                    for (int j = 0; j < pos.x; j++) {
                        if (a[i][j].valid) {
                            pos.x = j;
                            pos.y = i;
                            return;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}

//display Normal mode
void normalMode (Player& p){
    srand(time(0));
    getNormalBg(bg);

    Cell_1** a = new Cell_1* [BOARDHEIGHT];
    initBoard(a);

    goToXY(10, 0);
    cout << "NAME: " << p.name;
    goToXY(40, 0);
    cout << "POINT: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(92, 12);
    cout << "Press arrow to move";
    goToXY(92, 13);
    cout << "Pren ENTER to delete";
    goToXY(92, 14);
    cout << "Press ESC to quit to menu";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    Position select_pos[2] = {{-1, -1}, {-1, -1}};
    int pair = 2;
    Position cur_pos{0, 0};
    //0 playing the game
    //1 game over
    //2 choose ESC to quit the game mode
    int status = 0;

    while (!status && p.life){
        a[cur_pos.y][cur_pos.x].selected = 1;

        renderBoard(a);

        move(a, cur_pos, status, p, select_pos, pair);

        if (!checkValidPairs(a))
            status = 1;
    }

    renderBoard(a);
    deleteBoard(a);
    Sleep(500);
    system("cls");

    //check the win condition
    if (p.life != 0 && status == 1){
        displayStatus(true);
        goToXY(50, 17);
        char c;
        //ask player to play more or not
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");

        //if they choose "yes", continue normal mode
        //if they don't, exit normal mode and write the record into normal mode leaderboard
        if (c == 'Y' || c == 'y')
            normalMode(p);
        else 
            writeLeaderBoard(p, "Normal.txt");
    //the lost condition
    } else if (p.life == 0){
        displayStatus(false);
        writeLeaderBoard(p, "Normal.txt");
        Sleep(2000);
    }

    system("cls");
}