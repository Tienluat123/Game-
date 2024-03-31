#pragma once
#ifndef CHECKING
#define CHECKING

#include "Structure.h"
bool linecheck(Cell_1**, int , int , int , int );
bool Icheck(Cell_1**, int , int , int , int );
bool Lcheck(Cell_1**, int , int , int , int );
bool Zcheck(Cell_1**, int , int , int , int );
bool Ucheck(Cell_1**, int , int , int , int );
bool allcheck(Cell_1**, int , int , int , int );
bool checkValidPairs(Cell_1**);
bool suggestion(Cell_1**, Position&, Position&);

#endif