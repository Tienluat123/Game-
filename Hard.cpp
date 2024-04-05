#include "Hard.h"
#include <iostream>
using namespace std;

char BG[25][51];

//push the nodes in linked list forward
void push(Cell_2*& head, Cell_2* p) {
    if (head == NULL) {
        head = p;
    }
    else {
        Cell_2* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = p;
    }
}

//initialize the board with linked list
void initList(Cell_2** arr) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        arr[i] = NULL;
        for (int j = 0; j < 8; j++) {
            Cell_2* p = new Cell_2;
            p->i = i;
            p->j = j;
            p->next = NULL;
            push(arr[i], p);
        }
    }

    //creating characters is similar to the pointer array
    int flagNum = 20;
    while (flagNum) {
        int i, time = 2;
        char c = 65 + rand() % 10;
        while (time)
        {
            i = rand() % 5;
            int j = rand() % 8;
            Cell_2* p = findTheNode(arr, i, j);
            if (p->c == ' ') {
                p->c = c;
                time--;
            }
        }
        flagNum--;
    }
}

//delete the board when the game is over
void deleteList(Cell_2** arr) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        Cell_2* temp;
        while (arr[i] != NULL)
        {
            temp = arr[i];
            arr[i] = arr[i]->next;
            temp->deleteBox();
            if (temp->j < 4) displayHardBg(BG, temp->j, i);
            Sleep(200);
            delete temp;
        }
    }
    delete[]arr;
}

void renderList(Cell_2** arr) {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        Cell_2* temp = arr[i];
        while (temp != NULL)
        {
            temp->drawBox(112);
            temp = temp->next;
        }
    }
}

void control(Cell_2** arr, Position& pos, int& status, Player& p, Position selectedPos[], int& couple) {
    int temp, key;
    temp = _getch();
    //if the pressed key is not special key (arrow key)
    if (temp && temp != 224) {
        //if pressed the ESC
        if (temp == ESC_KEY) {
            status = 2;
        }
        //if pressed the ENTER
        else if (temp == ENTER_KEY) {
            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                Cell_2* temp = findTheNode(arr, pos.y, pos.x);
                temp->drawBox(70);
                Sleep(500);

                temp->selected = 0;
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
                findTheNode(arr, pos.y, pos.x)->selected = 1;
                couple--;

                //if the pair is chosen
                if (couple == 0) {
                    Cell_2* p1, * p2;
                    p1 = findTheNode(arr, selectedPos[0].y, selectedPos[0].x);
                    p2 = findTheNode(arr, selectedPos[1].y, selectedPos[1].x);
                    //if the pair character is the same
                    if (p1->c == p2->c) {
                        //check if the shape is valid
                        if (allCheck(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            p1->drawBox(40);
                            p2->drawBox(40);
                            Sleep(500);

                            DifMode(arr, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x, BG);
                        }
                        else {
                            p1->drawBox(70);
                            p2->drawBox(70);
                            Sleep(500);

                            p.life--;
                            PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        p1->drawBox(70);
                        p2->drawBox(70);
                        Sleep(500);

                        p.life--;
                        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\error.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }
                    //return to normal
                    p1->selected = 0;
                    p2->selected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < BOARDHEIGHT; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    //move to the valid box
                    for (int i = 0; i <= pos.y; i++) {
                        for (int j = 0; j <= pos.x; j++) {
                            if (findTheNode(arr, i, j) != NULL) {
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
    //if the pressed key is arrow key
    else
    {
        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //check if the box is chosen or not
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x))
            findTheNode(arr, pos.y, pos.x)->selected = 0;
        //movement is similar to the pointer array
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGHT - 1; j > pos.y; j--) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGHT; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (findTheNode(arr, j, i) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (findTheNode(arr, i, j) != NULL) {
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
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGHT; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (findTheNode(arr, i, j) != NULL) {
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

//it is similar to the normal mode
void hardMode(Player& p) {
    srand(time(0));
    getHardBg(BG);

    Cell_2** board = new Cell_2 * [BOARDHEIGHT];
    initList(board);

    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;

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
    cout << "|";
    for (int i = 0; i < 23; i++)
        cout << "-";
    goToXY(95, 16);
    cout << "|Correct match (+20pt)";
    goToXY(95, 17);
    cout << "|Wrong match (-1 life)";
    goToXY(95, 18);
    cout << "|NO SUGGESTION";
    goToXY(96, 19);
    for (int i = 0; i < 23; i++)
        cout << "-";
    for (int i = 0; i < 7; i++) {
        goToXY(95 + 24, 12 + i);
        cout << "|";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    Position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    Position curPosition{ 0, 0 };
    int status = 0;

    while (!status && p.life) {
        findTheNode(board, curPosition.y, curPosition.x)->selected = 1;

        renderList(board);

        control(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs(board))) status = 1;
    }

    renderList(board);
    deleteList(board);
    Sleep(500);
    system("cls");

    if (status == 2) {
        //update the leaderboard
        writeLeaderBoard(p, "Hard.txt");
        Sleep(500);
    }
    //if the life is 0 or the board is still not completed
    else if (p.life == 0 || (status == 1 && p.point < 400)) {
        //display lose status and update the leaderboard
        displayStatus(0);
        writeLeaderBoard(p, "Hard.txt");
        Sleep(500);
    }
    ///if the life is not 0 when finishing the board
    else if (p.life != 0) {
        //display win status
        displayStatus(1);
        goToXY(57, 17);
        cout << "You get a bonus life";
        p.life++;

        goToXY(50, 18);
        //ask the players whether they want continue or not 
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') hardMode(p);
        //if they choose not, update the leaderboard
        else writeLeaderBoard(p, "Hard.txt");
    }
    system("cls");
}