#pragma once 
#ifndef UTILITY 
#define UTILITY

#include <fstream>
#include <string>
#include "Setting.h"
#include "Structure.h"
using namespace std;

void sortLeaderBoard(Player [], int);
void printLeaderBoard(char&);
void writeLeaderBoard(Player, string);
void getPlayerInfor(Player&);
void displayStatus(bool);
void getNormalBg(char [][41]);
void displayNormalBg(char [][41], int, int);
void getHardBg(char [][51]);
void displayHardBg(char [][51], int, int);
int menu();

#endif