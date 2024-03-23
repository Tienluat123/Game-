#pragma once
#ifndef Console //check the condition that if the indentifier is not defined, the below code will run
#define Console

#include <windows.h>
void goToXY(int, int);
void resizeWindow(int, int);
void setCursor(bool);
void hideScrollBar();
void initWindow(int, int);

#endif