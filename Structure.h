#pragma once
#ifndef STRUCT
#define STRUCT

#include <string>
using namespace std;

//define the width and length of the game board
#define BOARDWIDTH 8
#define BOARDHEIGTH 5

//define the specific numbers for the keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

//struct for position
struct Position {
	int x, y;
};

//struct for player 
struct Player {
	string name = "";
	int point, life;
};

//struct for the first box when player choose
struct Cell_1 {
	int i, j;
	char c = ' ';
	bool valid = 1, selected = 0;

	void drawBox(int);
	void deleteBox();
};

//struct for the second box when player choose
struct Cell_2 {
	int i, j;
	char c = ' ';
	bool selected = 0;
	Cell_2* next;

	void drawBox(int);
	void deleteBox();
};

#endif