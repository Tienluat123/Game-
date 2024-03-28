#pragma once
#ifndef CONSOLE //check the condition that if the indentifier is not defined, the below code will run
#define CONSOLE

#include <Windows.h>
void goToXY(int, int);
void resizeWindow(int, int);
void setCursor(bool);
void hideScrollBar();
void initWindow(int, int);

#endif