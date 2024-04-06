#pragma once
#ifndef CONSOLE //check the condition that if the indentifier is not defined, the below code will run
#define CONSOLE
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "Structure.h"
#include <mmsystem.h>


void goToXY(int, int);
void resizeWindow(int, int);
void setCursor(bool);
void hideScrollBar();
void initWindow(int, int);
#endif