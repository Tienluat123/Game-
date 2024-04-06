#include "Structure.h"
#include "Setting.h"
#include<iostream>
using namespace std;

//box definition
char box[5][12] = {
    {" --------- "},
    {"|         |"},
    {"|         |"},
    {"|         |"},
    {" --------- "}
};

//draw box 
void Cell_1::drawBox (int color){
    if (!valid)
        return;
    
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++){
        goToXY(x * 10, y * 4 + i);
        cout << box[i];
    }

    if (selected){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c % 6 + 1)); // white background
        for (int i = 1; i < 4; i++) {
            goToXY(x * 10 + 1, y * 4 + i);
            cout << "         ";
        }

        goToXY(x * 10 + 5, y * 4 + 2);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    } else {
        goToXY(x * 10 + 5, y * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c % 6 + 1);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void Cell_1::drawHiddenBox (int color){
    if (!valid)
        return;
    
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++){
        goToXY(x * 10, y * 4 + i);
        cout << box[i];
    }

    if (selected){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c % 6 + 1)); // white background
        for (int i = 1; i < 4; i++) {
            goToXY(x * 10 + 1, y * 4 + i);
            cout << "         ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

//delete box 
void Cell_1::deleteBox() {
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++) {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";
    }
}

//THE SAME AS THE CELL_1
void Cell_2::drawBox(int color) {
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++) {
        goToXY(x * 10, y * 4 + i);
        cout << box[i];
    }

    if (selected) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (c % 6 + 1)); // white background
        for (int i = 1; i < 4; i++) {
            goToXY(x * 10 + 1, y * 4 + i);
            cout << "         ";
        }

        goToXY(x * 10 + 5, y * 4 + 2);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        goToXY(x * 10 + 5, y * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c % 6 + 1);
        cout << c;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
}

void Cell_2::deleteBox() {
    int x = j + 1, y = i + 1;

    for (int i = 0; i < 5; i++) {
        goToXY(x * 10, y * 4 + i);
        cout << "           ";
    }
}