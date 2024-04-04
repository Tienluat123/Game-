#include "PvP.h"
#include "Normal.h"

//current player turn
int cur_player = 1;


void movePvP(Cell_1** board, Position& pos, int& status, Player& p, Position selectedPos[], int& couple, int& cur_player) {
    int temp, key;
    temp = _getch();
    //if the pressed key is not special key (arrow key)
    if (temp && temp != 224) {
        //if pressed ESC
        if (temp == ESC_KEY) {
            status = 2;
        }
        //if pressed ENTER
        else if (temp == ENTER_KEY) {
            //play enter sound
            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);

                board[selectedPos[0].y][selectedPos[0].x].selected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                if (cur_player <= 1) {
                    cur_player = 2;
                    PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    goToXY(30, 2);
                    cout << "Life: " << p.life;
                }
                else {
                    cur_player = 1;
                    PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    goToXY(70, 2);
                    cout << "Life: " << p.life;
                }
            } 
            //check the repetition
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].selected = 1;
                couple--;

                //if players have chosen a pair
                if (couple == 0) {
                    //if the pair characters are correct
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {
                        //if the shape is correct
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            p.point += 20;
                            if (cur_player <= 1) {
                                cur_player = 2;
                                goToXY(10, 1);
                                cout << "Point: " << p.point;
                            }
                            else {
                                cur_player = 1;
                                goToXY(70, 1);
                                cout << "Point: " << p.point;
                            }

                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].valid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();

                            board[selectedPos[1].y][selectedPos[1].x].valid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                        }
                        else {
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            p.life--;
                            if (cur_player <= 1) {
                                cur_player = 2;
                                goToXY(10, 2);
                                PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                cout << "Life: " << p.life;
                            }
                            else {
                                cur_player = 1;
                                goToXY(70, 2);
                                PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                cout << "Life: " << p.life;
                            }
                            goToXY(70, 0);
                            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        p.life--;
                        if (cur_player <= 1) {
                            cur_player = 2;
                            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            goToXY(10, 2);
                            cout << "Life: " << p.life;
                        }
                        else {
                            cur_player = 1;
                            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            goToXY(70, 2);
                            cout << "Life: " << p.life;
                        }
                        
                    }
                    // return to normal
                    board[selectedPos[0].y][selectedPos[0].x].selected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].selected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };
                    

                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (board[i][j].valid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    //move to valid box
                    for (int i = 0; i <= pos.y; i++) {
                        for (int j = 0; j <= pos.x; j++) {
                            if (board[i][j].valid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else //if pressed keys are arrow keys
    //movement
    {
        //play movement sound
        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            board[pos.y][pos.x].selected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (board[j][i].valid) {
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
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].valid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].valid) {
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
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].valid) {
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
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].valid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].valid) {
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

void pvpMode (Player& p1, Player& p2){
    //get the background of normal mode
    srand(time(0));

    //initialize the board
    Cell_1** board = new Cell_1 * [BOARDHEIGHT];
    initBoard(board);

    //print the name, point and life on the screen
    goToXY(10, 0);
    cout << "Name: " << p1.name;
    goToXY(10, 1);
    cout << "Point: " << p1.point;
    goToXY(10, 2);
    cout << "Life: " << p1.life;

    goToXY(70, 0);
    cout << "Name: " << p2.name;
    goToXY(70, 1);
    cout << "Point: " << p2.point;
    goToXY(70, 2);
    cout << "Life: " << p2.life;

    //print the introduction on the screen
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(96, 11);
    for (int i = 0; i < 23; i++)
        cout << "-";
    goToXY(95, 12);
    cout << "|Press arrow key to move";
    goToXY(95, 13);
    cout << "|Press Enter to choose";
    goToXY(95, 14);
    cout << "|Press ESC to quit";
    goToXY(95, 15);
    cout << "|Correct match (+20pt)";
    goToXY(95, 16);
    cout << "|Wrong match (-1 life)";
    goToXY(95, 17);
    cout << "|NO SUGGESTION";
    goToXY(96, 18);
    for (int i = 0; i < 23; i++)
        cout << "-";
    for (int i = 0; i < 6; i++) {
        goToXY(95 + 24, 12 + i);
        cout << "|";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    //the coord of 2 boxes that player have chosen
    Position selectedPos[] = { {-1, -1}, {-1, -1} };
    //counting how many box player have chosen
    int couple = 2;
    //current position of the box cursor
    Position curPosition{ 0, 0 };
    int status = 0; //0. playing game
                    //1. game is over
                    //2. players choose to exit

    //while status is 0 and life is not 0 
    while (status == 0 && p1.life != 0 && p2.life != 0) {
        board[curPosition.y][curPosition.x].selected = 1;

        renderBoard(board);

        if (cur_player == 1) {
            goToXY(50, 3);
            cout << "It's " << p1.name << " turn";
        }
        else {
            goToXY(55, 3);
            cout << p2.name;
        }

        movePvP(board, curPosition, status, p1, selectedPos, couple, cur_player);
        if (cur_player == 2){
            movePvP(board, curPosition, status, p2, selectedPos, couple, cur_player);

        }

        //if there are no valid pairs left, the game is over
        if ((!checkValidPairs(board))) status = 1;
    }

    renderBoard(board);
    deleteBoard(board);
    Sleep(500);
    system("cls");

    //if players choose ESC
    if (status == 2){
        Sleep(500);
    }  
    else if (p1.life == 0 || p2.life == 0 || (status == 1)) {
        if (p1.life == 0 && p2.life != 0){
            goToXY(53, 17);
            cout << "Player " << p2.name << " win";
        } else if (p2.life == 0 && p1.life != 0){
            goToXY(53, 17);
            cout << "Player " << p1.name << " win";
        } else if (p1.life != 0 && p2.life != 0){
            if (p1.point > p2.point){
                goToXY(53, 17);
                cout << "Player " << p1.name << " win";
            } else if (p1.point < p2.point){
                goToXY(53, 17);
                cout << "Player " << p2.name << " win";
            } else {
                goToXY(57, 17);
                cout << "DRAW";
            }
        }
        displayStatus(1);
        Sleep(500);

        //ask the players whether they want continue or not
        goToXY(50, 18); 
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') pvpMode(p1, p2);
    }

    system("cls");
}