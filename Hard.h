#pragma once
#include "CheckingLinkedList.h"
#include <conio.h>
#include <time.h>
#include "Setting.h"
#include "Utility.h"

void push(Cell_2*&, Cell_2*);
void initList(Cell_2**);
void deleteList(Cell_2**);
void renderList(Cell_2**);
void control(Cell_2**, Position&, int&, Player&, Position[], int&);
void hardMode(Player&);