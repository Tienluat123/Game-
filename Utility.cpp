#include "Utility.h"
#include <iostream>
#include <conio.h>

//sort the leaderboard
void sortLeaderBoard (Player list[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (list[i].point < list[j].point){
                swap(list[i], list[j]);
            }
        }
    }
}

//read the file and print the leaderboard on the console
void printLeaderBoard(char &c) {
    //choose the mode leaderboard 
    goToXY(45, 15);
    cout << "Which mode you want to see? (N/H): ";
    cin >> c;
    string filename;
    if (c == 'n' || c == 'N'){
        filename = "Normal.txt";
    } else if (c == 'h' || c == 'H'){
        filename = "Hard.txt";
    } else {
        system("cls");
        return;
    }
    system("cls");

    //print title of the leaderboard
    goToXY(30, 5);
    for (int i = 0; i < 75; i++) {
        cout << "_";
    }
    goToXY(63, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "LEADERBOARD";
    goToXY(29, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "|";
    goToXY(30, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "RANK";
    goToXY(45, 6);
    cout << "NAME";
    goToXY(100, 6);
    cout << "POINT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "|";
    goToXY(30, 7);
    for (int i = 0; i < 75; i++) {
        cout << "_";
    }
    cout << "|";

    //open file to read
    ifstream f;
    f.open(filename);
    if (f) {
        Player p;

        //read and print the information of the players of the file
        int i = 0, rank = 1;
        while (getline(f, p.name, ' ')) {
            f >> p.point;
            f.get();

            goToXY(29, 7 + i);
            cout << "|";
            goToXY(30, 7 + i);
            for (int j = 0; j < 75; j++) {
                cout << "_";
            }
            cout << "|";

            //change the text color for 3 highest player
            goToXY(29, 8 + i);
            cout << "|";
            goToXY(30, 8 + i);
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 - i / 2);
            cout << rank++;
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 - i / 2);
            goToXY(45, 8 + i);
            cout << p.name;
            goToXY(100, 8 + i);
            cout << p.point;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            goToXY(105, 8 + i);
            cout << "|";
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            i += 2;
        }
        goToXY(29, 7 + i);
        cout << "|";
        goToXY(30, 7 + i);
        for (int i = 0; i < 75; i++) {
            cout << "_";
        }
        goToXY(105, 7 + i);
        cout << "|";
        f.close();
    }
  
    //wait until another key is pressed to clear screen
    _getch();
    system("cls");
}

//update the leaderboard with a new player entry
void writeLeaderBoard(Player p, string filename) {
    //open the file
    ifstream fin(filename);
    //if the file is opened
    if (fin) {
        Player* list = new Player[11];
        int no_player = 0;
        string s;

        //get all infor of the old file
        while (getline(fin, s, ' ')) {
            list[no_player].name = s;
            fin >> list[no_player].point;
            fin.ignore();
            no_player++;
        }

        //update the new entry
        bool found = false;
        //if the player already have account then update the point
        for (int i = 0; i < no_player; i++){
            if (p.name == list[i].name){
                found = true;
                if (p.point > list[i].point){
                    list[i].point = p.point;
                    break;
                }
            }
        }
        //if the player is new and the leaderboard is not full, add new player into the leaderboard
        if (found == false && no_player < 10){
            list[no_player].name = p.name;
            list[no_player].point = p.point;
            no_player++;
        //if the leaderboard is full, add new player into the board and sort the board, after that take 10 highest score 
        } else if (found == false && no_player >= 10){
            sortLeaderBoard(list, no_player);
            if (list[no_player - 1].point < p.point){
                list[no_player - 1].name = p.name;
                list[no_player - 1].point = p.point;
            }
        }

        sortLeaderBoard(list, no_player);

        
        fin.close();

        //write the new information into the file
        ofstream fout(filename);

        for (int i = 0; i < no_player; i++) {
            fout << list[i].name << " " << list[i].point << endl;
        }

        fout.close();

        delete[]list;
    }
    else {
        //handle the new leaderboard with no information
        ofstream fout(filename);
        fout << p.name << " " << p.point << endl;
        fout.close();
    }
}

//get the information of the new user
void getPlayerInfor(Player& p) {
    goToXY(35, 12);
    cout << "Enter player name (under 10 characters please): ";
    cin >> p.name;
    cin.ignore();
    p.life = 3;
    p.point = 0;
}

//display the status of the game on the console when the game is over
void displayStatus(bool win) {
    if (win) {
        //play win sound
        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\win.wav"), NULL, SND_FILENAME | SND_ASYNC);
        //print "you won" when variable "win" is true
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        goToXY(50, 10);
        cout << "__  ______  __  __  _      ______  _  __";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / | | /| / / __ \\/ |/ /";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ /  | |/ |/ / /_/ /    /";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/   |__/|__/\\____/_/|_/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        //play lose sound
        PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\lose.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        //print "you lose" when variable "win" is false
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        goToXY(50, 10);
        cout << "__  ______  __  __  __   ____  ________";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / / /  / __ \\/ __/ __/";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ / / /__/ /_/ /\\ \\/ _/";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/ /____/\\____/___/___/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        goToXY(50, 15);
        cout << "Press any key to back to the main menu";
        //pressed any key to back to the menu
        _getch();
        PlaySound(0, 0, 0);
    }
}

// get the background of the board (normal mode)
//store the background into a char array
void getNormalBg(char bg[][41]) {
    ifstream fin;
    fin.open("pika.txt");
    if (fin) {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 41; j++)
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        //If the file doesn't exist, it fills the bg array with space characters
        memset(bg, ' ', sizeof(bg));
    }
}

//display the background on the console (normal mode)
void displayNormalBg(char bg[][41], int x, int y) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            goToXY((x + 1) * 10 + j, (y + 1) * 4 + i);
            cout << bg[y * 4 + i][x * 10 + j];
        }
    }
    //after printing the background image, it resets the text attribute to the default color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//get the background of the the board (hard mode)
void getHardBg(char bg[][51]) {
    ifstream fin;
    fin.open("hcmus.txt");
    if (fin) {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 51; j++)
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        //If the file doesn't exist, it fills the bg array with space characters
        memset(bg, ' ', sizeof(bg));
    }
}

//display the background on the console (hard mode)
void displayHardBg(char bg[][51], int x, int y) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            goToXY((x + 1) * 10 + j, (y + 1) * 4 + i);
            cout << bg[y * 4 + i][x * 10 + j];
        }
    }
    //after printing the background image, it resets the text attribute to the default color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//display the menu of the game on the console
int menu() {
    //create an array of choice of the menu
    int choice[5] = { 0,0,0,0,0 }, cur_choice = 0; //cur_choice is the choice of the user

    //print the title of the game on the console
    goToXY(35, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << " ______    __   __  ___      ___       ______  __    __   __    __";
    goToXY(35, 3);
    cout << "|   _  \\  |  | |  |/  /     /   \\     /      ||  |  |  | |  |  |  |";
    goToXY(35, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "|  |_)  | |  | |  '  /     /  ^  \\   |  ,----'|  |__|  | |  |  |  |";
    goToXY(35, 5);
    cout << "|   ___/  |  | |    <     /  /_\\  \\  |  |     |   __   | |  |  |  |";
    goToXY(35, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "|  |      |  | |  .  \\   /  _____  \\ |  `----.|  |  |  | |  `--'  |";
    goToXY(35, 7);
    cout << "| _|      |__| |__|\\__\\ /__/     \\__\\ \\______||__|  |__|  \\______/";

    //Play background sound
    PlaySound(TEXT("H:\\C C++\\Project_KTLT\\Project_KTLT\\sound\\background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //handle the choices of the user
    while (1) {

        choice[cur_choice] = 1; //the choice of the user

        //if user's choice is the first choice
        //the color changes based on the option is chosen or not
        if (choice[0]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 11 + i);
                cout << "             ";
            }

            goToXY(64, 12);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 3);
            cout << "NORMAL";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 11 + i);
                cout << "             ";
            }

            goToXY(64, 12);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            cout << "NORMAL";
        }

        //if user's choice is the second choice
        if (choice[1]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 14 + i);
                cout << "             ";
            }

            goToXY(62, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 4);
            cout << "DIFFICULT";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 14 + i);
                cout << "             ";
            }

            goToXY(62, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "DIFFICULT";
        }

        //if user's choice is the third choice
        if (choice[2]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(61, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 2);
            cout << "LEADERBOARD";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 17 + i);
                cout << "             ";
            }

            goToXY(61, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << "LEADERBOARD";
        }

        //if user's choice is the fourth choice
        if (choice[3]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(65, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 5);
            cout << "PVP";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            for (int i = 0; i < 3; i++) {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(65, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            cout << "PVP";
        }

        //if user's choice is the last choice
        if (choice[4]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 23 + i);
                cout << "             ";
            }

            goToXY(64, 24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 6);
            cout << "EXIT";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            for (int i = 0; i < 3; i++) {
                goToXY(60, 23 + i);
                cout << "             ";
            }

            goToXY(64, 24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            cout << "EXIT";
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        //check keyboard input
        int temp;
        if (temp = _getch()) {
            //check if it not special key (arrow)
            if (temp != 224 && temp)
            {
                // check if it is ENTER key
                //if it is, clear screen and return current choice 
                if (temp == ENTER_KEY) {
                    system("cls");
                    PlaySound(0, 0, 0);
                    return cur_choice;
                }
            } else {
                //if it is special key (arrow)
                int key;
                key = _getch(); //get the special key
                switch (key)
                {
                case KEY_UP: // if it is arrow UP, move up 1 position
                    choice[cur_choice] = 0;
                    if (cur_choice > 0) cur_choice--; // if current choice is at the first choice and user presses move up, go to the last choice
                    else cur_choice = 4;
                    break;
                case KEY_DOWN: //if it is arrow DOWN, move down 1 position
                    choice[cur_choice] = 0;
                    if (cur_choice < 4) cur_choice++; //if current choice is at the last choice and user presses move down, return to the first choice
                    else cur_choice = 0; 
                default:
                    break;
                }
            }
        }
    }
}