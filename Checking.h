#pragma once
#ifndef CHECKING
#define CHECKING

#include <Structure.h>
bool nextCheck(Cell_1**, int p1, int p2, int q1, int q2);
bool lineCheck(Cell_1**, int p1, int p2, int q1, int q2);
bool Icheck(Cell_1**, int p1, int p2, int q1, int q2);
bool Lcheck(Cell_1**, int p1, int p2, int q1, int q2);
bool Zcheck(Cell_1**, int p1, int p2, int q1, int q2);
bool Ucheck(Cell_1**, int p1, int p2, int q1, int q2);
bool allcheck(Cell_1**, int p1, int p2, int q1, int q2);
bool checkValidPairs(Cell_1**);

#endif