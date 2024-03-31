#pragma once
#ifndef LINKED_LIST
#define LINKED_LIST

#include "Structure.h"
#include "Utility.h"

Cell_2* findTheNode(Cell_2**, int, int);
bool Icheck(Cell_2**, int, int, int, int);
bool Lcheck(Cell_2**, int, int, int, int);
bool UandZcheck(Cell_2**, int, int, int, int);
bool allCheck(Cell_2**, int, int, int, int);
void deleteNode(Cell_2**, int, int, char [][51]);
void DifMode(Cell_2**, int, int, int, int, char [][51]);
bool checkValidPairs(Cell_2**);

#endif