#pragma once 
#ifndef MENU 
#define MENU

#include <fstream>
#include <string>
#include <Setting.h>
#include <Structure.h>
using namespace std;

void sortLeaderBoard(Player [], int);
void printLeaderBoard(string);
void writeLeaderBoard(Player, string);
void getPlayerInfor(Player&);
void displayStatus(bool);
void getNormalBg(char [][41]);
void displayNormalBg(char [][41], int, int);
int menu();
#endif