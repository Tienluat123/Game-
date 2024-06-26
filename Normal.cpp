#include "Normal.h"
#include <iostream>
using namespace std;

char bg[20][41];
//Cell_1** prevBoard = NULL;

//initialize the board for the normal mode
void initBoard(Cell_1** board) {
    //dynamic allocate the board and asign the coord for each box
    for (int i = 0; i < BOARDHEIGHT; i++) {
        board[i] = new Cell_1[BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    //assign a character for each box in the board
    int flagNum = (BOARDWIDTH * BOARDHEIGHT) / 2;
    while (flagNum) { 
        //the index and the time that character appears
        int index, time = 2;
        //random the character
        char c = 65 + rand() % 8;
        //assign the character into the board
        while (time) {
            //get the random coord 
            index = rand() % 40;
            if (board[index / 8][index % 8].c == ' ') {
                board[index / 8][index % 8].c = c;
                time--;
            }
        }
        flagNum--;
    }
}

//delete the board when the game is over
void deleteBoard(Cell_1** board) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            //if there are still valid boxes, delete them
            if (board[i][j].valid) {
                board[i][j].deleteBox();
                displayNormalBg(bg, j, i);
                Sleep(200);
            }
        }
    }

    //deallocate the board
    for (int i = 0; i < BOARDHEIGHT; i++) {
        delete[]board[i];
    }
    delete[]board;
}

//render the board
void renderBoard(Cell_1** board) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].drawBox(112);
        }
    }
}

//control system
void control(Cell_1** board, Position& pos, int& status, Player& p, Position selectedPos[], int& couple, int &suggest) {
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
            //check if 2 chosen pairs is the same or not, if they are the same , lose life point. 
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);

                //reset the choice pair
                board[selectedPos[0].y][selectedPos[0].x].selected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                goToXY(70, 0);
                cout << "Life: " << p.life;
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
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            //draw boxes in green color
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            //delete the pair
                            board[selectedPos[0].y][selectedPos[0].x].valid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            displayNormalBg(bg, selectedPos[0].x, selectedPos[0].y);

                            board[selectedPos[1].y][selectedPos[1].x].valid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                            displayNormalBg(bg, selectedPos[1].x, selectedPos[1].y);
                        }
                        else {
                            //draw boxes in red color
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            //lose life point 
                            p.life--;
                            goToXY(70, 0);
                            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        //draw box in red color
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        //lose life point
                        p.life--;
                        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // reset the choice pair
                    board[selectedPos[0].y][selectedPos[0].x].selected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].selected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    //move to the valid box
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
        //if the players press SPACE key
        else if (temp == SPACE_KEY) {
            ///check if the suggestion moves is not 0
            if (suggest > 0) {
                //check if the suggestion move find a valid pair
                if (suggestion(board, selectedPos[0], selectedPos[1])) {
                    p.point += 10;
                    suggest--;
                    goToXY(40, 0);
                    cout << "Point: " << p.point;
                    goToXY(90, 0);
                    cout << "Suggestion: " << suggest;

                    //delete the pair
                    board[selectedPos[0].y][selectedPos[0].x].valid = 0;
                    board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                    displayNormalBg(bg, selectedPos[0].x, selectedPos[0].y);

                    board[selectedPos[1].y][selectedPos[1].x].valid = 0;
                    board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                    displayNormalBg(bg, selectedPos[1].x, selectedPos[1].y);
                }
                else {
                    //if it cannot find a valid pair, do nothing
                    return;
                }

                //reset to normal
                couple = 2;
                selectedPos[0] = { -1, -1 };
                selectedPos[1] = { -1, -1 };

                return;
            }
            else {
                //if suggestion move is 0, do nothing
                return;
            }
        }
    }
    else //if pressed keys are arrow keys
    //movement
    {
        //play movement sound
        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //choose a box
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

//the board of the normal mode
void normalMode(Player& p) {
    //get the background of normal mode
    srand(time(0));
    getNormalBg(bg);

    //initialize the board
    Cell_1** board = new Cell_1 * [BOARDHEIGHT];
    initBoard(board);
    //suggestion 
    int suggest = 3;

    //print the name, point and life on the screen
    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;
    goToXY(90, 0);
    cout << "Suggestion: " << suggest;

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
    cout << "|Press SPACE to suggest";
    goToXY(95, 15);
    cout << "|Press ESC to quit";
    goToXY(95, 16);
    cout << "|";
    for (int i = 0; i < 23; i++)
        cout << "-";
    goToXY(95, 17);
    cout << "|-Correct match (+20pt)";
    goToXY(95, 18);
    cout << "|-Wrong match (-1 life)";
    goToXY(95, 19);
    cout << "|-Suggest will delete ";
    goToXY(95, 20);
    cout << "|a pair for you ";
    goToXY(95, 21);
    cout << "|-Use suggestion (+10pt)";
    goToXY(96, 22);
    for (int i = 0; i < 23; i++)
        cout << "-";
    for (int i = 0; i < 10; i++){
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
    while (status == 0 && p.life != 0) {
        board[curPosition.y][curPosition.x].selected = 1;

        renderBoard(board);

        control(board, curPosition, status, p, selectedPos, couple, suggest);

        //if there are no valid pairs left, the game is over
        if ((!checkValidPairs(board))) status = 1;
    }

    renderBoard(board);
    deleteBoard(board);
    Sleep(500);
    system("cls");

    //if players choose ESC
    if (status == 2){
        //update the leaderboard
        writeLeaderBoard(p, "H:\\C C++\\Project_KTLT\\Project_KTLT\\record\\Normal.txt");
        Sleep(500);
    }  
    //if the life is 0 or the board is still not completed
    else if (p.life == 0 || (status == 1 && p.point < 370)) {
        //display lose status and update the leaderboard
        displayStatus(0);
        writeLeaderBoard(p, "H:\\C C++\\Project_KTLT\\Project_KTLT\\record\\Normal.txt");
        Sleep(500);
    }
    ///if the life is not 0 and point is not negative when finishing the board
    else if (p.life != 0 && status == 1) {
        //display win status
        displayStatus(1);
        goToXY(56, 17);
        cout << "You get a bonus life";
        p.life++;

        goToXY(50, 18);
        //ask the players whether they want continue or not 
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') normalMode(p);
        //if they choose not, update the leaderboard
        else writeLeaderBoard(p, "H:\\C C++\\Project_KTLT\\Project_KTLT\\record\\Normal.txt");
    }

    system("cls");
}