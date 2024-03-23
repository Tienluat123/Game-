#include <Utility.h>
#include <iostream>
#include <conio.h>

//read the file adn print the leaderboard on the console
void printLeaderBoard(string filename) {
    //print the title of the leaderboard
    goToXY(60, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "LEADERBOARD";
    goToXY(30, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "NAME";
    goToXY(100, 6);
    cout << "POINT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    goToXY(30, 7);

    //open file to read
    ifstream f;
    f.open(filename);
    //if the file is opened
    if (f) {
        Player p;

        //read and print the information of the players of the file
        int i = 0;
        while (getline(f, p.name, ' ')) {
            f >> p.point;
            f.get();
            goToXY(30, 7 + i);
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 - i / 2);
            goToXY(30, 8 + i);
            cout << p.name;
            goToXY(100, 8 + i);
            cout << p.point;
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            i += 2;
        }
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
        Player* list = new Player[10];
        int no_player = 0;
        string s;

        //get all infor of the old file
        while (getline(fin, s, ' ')) {
            list[no_player].name = s;
            fin >> list[no_player].point;
            fin.get();
            no_player++;
        }

        //update the new entry 
        //get the position of the new entry in the leaderboard
        int index = no_player - 1;
        for (index; index >= 0; index--) {
            if (p.point <= list[index].point) {
                break;
            }
        }

        //if the quantity of the leaderboard is not over 10, insert the new entry into the leaderboard
        if (no_player < 10) {
            for (int i = no_player; i > index + 1; i--) {
                list[i] = list[i - 1];
            }
            list[index + 1] = p;
            no_player++;
        }
        else {
            //if the quantity is over 10, the new player's points are higher than the points of the player at the lowest position, the function inserts the new player entry at the determined index
            if (index != no_player - 1) {
                for (int i = no_player - 1; i > index + 1; i--) {
                    list[i] = list[i - 1];
                }
                list[index + 1] = p;
            }
        }
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
    goToXY(50, 12);
    cout << "Enter player name: ";
    cin >> p.name;
    cin.ignore();
    p.life = 3;
    p.point = 0;
}

//display the status of the game on the console when the game is over
void displayStatus(bool win) {
    if (win) {
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
    }
}

//display the menu of the game on the console
int menu() {
    //create an array of choice of the menu
    int choice[4] = { 0,0,0,0 }, cur_choice = 0; //cur_choice is the choice of the user

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

        //if user's choice is the last choice
        if (choice[3]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(64, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 6);
            cout << "EXIT";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            for (int i = 0; i < 3; i++) {
                goToXY(60, 20 + i);
                cout << "             ";
            }

            goToXY(64, 21);
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
                    else cur_choice = 3;
                    break;
                case KEY_DOWN: //if it is arrow DOWN, move down 1 position
                    choice[cur_choice] = 0;
                    if (cur_choice < 3) cur_choice++; //if current choice is at the last choice and user presses move down, return to the first choice
                    else cur_choice = 0; 
                default:
                    break;
                }
            }
        }
    }
}