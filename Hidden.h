#pragma once 
#include "Checking.h"
#include "Setting.h"
#include "Structure.h"
#include "Utility.h"
#include "Normal.h"
#include <conio.h>
#include <ctime>
#include <iostream>

void renderHiddenBoard (Cell_1**);
void controlHidden(Cell_1**, Position& , int& , Player&, Position[], int& , int &);
void hiddenMode (Player&);