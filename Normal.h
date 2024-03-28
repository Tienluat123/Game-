#pragma once 
#include "Checking.h"
#include "Setting.h"
#include "Utility.h"
#include <conio.h>
#include <ctime>
#include <iostream>

void initBoard(Cell_1**);
void renderBoard(Cell_1**);
void deleteBoard(Cell_1**);
//void deleteBoardWhenLose(Cell_1**);
void move(Cell_1**, Position&, int&, Player&, Position[], int& );
void normalMode(Player&);