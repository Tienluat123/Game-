#pragma once 
#ifndef MENU 
#define MENU

#include <fstream>
#include <string>
#include <Setting.h>
#include <Structure.h>
using namespace std;

void printLeaderBoard(string);
void writeLeaderBoard(Player, string);
void getPlayerInfor(Player&);
void displayStatus(bool);
void getBG(char [][41]);
void displayBG(char [][41], int, int);
int menu();
#endif