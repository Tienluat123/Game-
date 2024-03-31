#include "Checking.h"

//check if if there is a line (sequence of consecutive valid boxes) between two chosen boxes on a game board.
bool linecheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    //horizontal
    if (p1 == q1) {
        int y, x, dem = 0;
        //determines the starting and ending column indices
        if (p2 > q2) {
            x = q2;
            y = p2;
        }
        else {
            x = p2;
            y = q2;
        }
        //count the valid boxes from starting to ending index
        for (int i = x; i <= y; i++) {
            //check if the current box is valid or not
            if (board[p1][i].valid) {
                dem++;
                //it finds two consecutive valid boxes, it returns false, indicating there is no line.
                if (dem == 2) return false;
            }
        }
        //If it finds only one valid box and the chosen boxes have opposite validity, return true, there is a line
        if ((dem == 1) && ((!board[p1][p2].valid && board[q1][q2].valid) || (board[p1][p2].valid && !board[q1][q2].valid))) {//sai
            return true;
        }
        //if there is no box, return true, there is a line
        else if (dem == 0) {
            return true;
        }
        return false;
    }

    //vertical
    //vice versa to the horizontal
    if (p2 == q2) {
        int x, y, dem = 0;
        if (p1 > q1) {
            x = q1;
            y = p1;
        }
        else {
            x = p1;
            y = q1;
        }
        for (int i = x; i <= y; i++) {
            if (board[i][p2].valid) {
                dem++;
                if (dem == 2) return false;
            }
        }
        if ((dem == 1) && ((!board[p1][p2].valid && board[q1][q2].valid) || (board[p1][p2].valid && !board[q1][q2].valid))) {//sai
            return true;
        }
        else if (dem == 0) {
            return true;
        }
        return false;
    }
    return false;
}

//check if 2 chosen boxes are connected in a I shape
bool Icheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    // horizontal
    if (p1 == q1) {
        int y, x, dem = 0;
        if (p2 > q2) {
            x = q2;
            y = p2;
        }
        else {
            x = p2;
            y = q2;
        }
        //check from p2 to q2 if there is any boxes
        for (int i = x + 1; i < y; i++) {
            //if there is a box, return false, there is no line
            if (board[p1][i].valid) {
                return false;
            }
        }
        return true;
    }
    //vertical
    //similar to horizontal 
    if (p2 == q2) {
        int x, y, dem = 0;
        if (p1 > q1) {
            x = q1;
            y = p1;
        }
        else {
            x = p1;
            y = q1;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[i][p2].valid) {
                return false;
            }
        }
        return true;
    }
    return false;
}

//if the 2 chosen boxes are conneccted int a L shape
bool Lcheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    //if 2 chosen boxes are on the same line, return false
    if (p1 == q1 || p2 == q2) {
        return false;
    }
    bool c1, c2;
    //check if the top right corner of the potential L shape 
    //if it not valid, it considers two possible line patterns
    if (!board[p1][q2].valid) {
        //line from p1, p2 to p1, q2 "|     "
        c1 = linecheck(board, p1, p2, p1, q2);
        //line from q1, q2 to p1, q2 "------"
        c2 = linecheck(board, q1, q2, p1, q2);

        //if 2 lines are valid, return true
        if (c1 && c2) {
            return true;
        }
    }
    //check if the the bottom right corner of the potential L shape
    //if it not valid, it considers two possible line patterns
    if (!board[q1][p2].valid) {
        //line from p1, p2 to q1, p2 "------"
        c1 = linecheck(board, p1, p2, q1, p2);
        //line from q1, q2 to q1, p2 "     |"
        c2 = linecheck(board, q1, q2, q1, p2);
        //if 2 lines are valid, return true
        if (c1 && c2) {
            return true;
        }
    }
    return false;
}

//check if the 2 chosen boxes are connected in a Z shape
bool Zcheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    //if 2 chosen boxes on the same line, return false
    if (p1 == q1 || p2 == q2) {
        return false;
    }
    bool c1, c2, c3;
    int x, y;
    //find which is bigger x2 or y2 then assign the smaller for p and other for q
    if (q2 < p2) {
        x = q2;
        y = p2;
    }
    else {
        x = p2;
        y = q2;
    }
    //check horizontal Z shape
    for (int i = x + 1; i < y; i++) {
        //the horizontal line must be in the range (p2, q2)
        c3 = linecheck(board, p1, i, q1, i);
        //if there is a horizontal line, continue checking 2 vertical lines
        if (c3) {
            //line from p1, p2 to the horizontal line
            c1 = linecheck(board, p1, p2, p1, i);
            //line from q1, q2 to the horizontal line
            c2 = linecheck(board, q1, q2, q1, i);
            //if 2 lines is valid, return true
            if (c1 && c2)
                return true;
        }
    }
    //checking vertical Z shape is similar to checking horizontal Z shape
    if (q1 < p1) {
        x = q1;
        y = p1;
    }
    else {
        x = p1;
        y = q1;
    }
    for (int i = x + 1; i < y; i++) {
        //the vertical line must be in the range of (p1, q1)
        c3 = linecheck(board, i, p2, i, q2);
        //if there is a vertical line, continue checking 2 horizontal line
        if (c3) {
            //line from p1, p2 to the vertical line
            c1 = linecheck(board, p1, p2, i, p2);
            //line from q1, q2 to the vertical line
            c2 = linecheck(board, q1, q2, i, q2);
            //if 2 lines is valid, return true
            if (c1 && c2)
                return true;
        }
    }
    //if 2 cases are wrong, return false
    return false;
}

//check if the 2 chosen boxes are connected in U shape
bool Ucheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    //check if the 2 chosen boxes is at the border of the board, it is a U shape
    if (((p1 == q1) && (p1 == 0 || p1 == BOARDHEIGHT - 1) || ((p2 == q2) && (p2 == 0 || q2 == BOARDWIDTH - 1)))) {
        return true;
    }
    bool c1, c2, c3;
    int x, y;
    //find which is bigger p2 or q2 then assign the smaller for p and other for q
    if (q2 < p2) {
        x = q2;
        y = p2;
    }
    else {
        x = p2;
        y = q2;
    }
    //check the horizontal U shape
    for (int i = 0; i < BOARDWIDTH; i++) {
        if (i <= x || i >= y) {
            //the vertical line must be out of the range (p2, q2)
            c3 = linecheck(board, p1, i, q1, i);
            //if the vertical line is valid, continue checking 2 horizontal line
            if (c3) {
                //line from p1, p2 to the vertical line
                c1 = linecheck(board, p1, p2, p1, i);
                //line from q1, q2 to the vertical line
                c2 = linecheck(board, q1, q2, q1, i);
                //if 2 lines are valid, return true
                if (c1 && c2) {
                    return true;
                }
            }
            //if the vertical line is out of the board
            else if (i == 0 || i == (BOARDWIDTH - 1)) {
                //just need to check 2 horizontal lines
                //continue check 2 horizontal lines
                c1 = linecheck(board, p1, p2, p1, i);
                c2 = linecheck(board, q1, q2, q1, i);
                if ((c1 && c2) || (c1 && q2 == i) || (p2 == i && c2)) {
                    return true;
                }
            }
        }
    }

    //checking the vertical U shape is similar to checking the horizontal U shape
    if (q1 < p1) {
        x = q1;
        y = p1;
    }
    else {
        x = p1;
        y = q1;
    }
    for (int i = 0; i < BOARDHEIGHT; i++) {
        if (i <= x || i >= y) {
            c3 = linecheck(board, i, p2, i, q2);
            if (c3) {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDHEIGHT - 1)) {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if ((c1 && c2) || (c1 && q1 == i) || (p1 == i && c2)) {
                    return true;
                }
            }
        }
    }
    //if 2 cases are wrong, return false
    return false;
}

//check all the possible cases
bool allcheck(Cell_1** board, int p1, int p2, int q1, int q2) {
    if (Icheck(board, p1, p2, q1, q2)) {
        return true;
    }
    else if (Lcheck(board, p1, p2, q1, q2)) {
        return true;
    }
    else if (Zcheck(board, p1, p2, q1, q2)) {
        return true;
    }
    else if (Ucheck(board, p1, p2, q1, q2)) {
        return true;
    }
    return false;
}

//check whether there exist valid pairs of cells with the same character
bool checkValidPairs(Cell_1** board) {
    //create the first character A
    char check = 'A';
    //loop from A to Z to check
    while (check >= 'A' && check <= 'Z') {
        int cnt = 0;

        //counts the occurrences of the current character check on the game board and stores their positions in the pos array
        int* pos = new int[BOARDHEIGHT * BOARDWIDTH];
        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].c == check && board[i][j].valid) {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }

        // check the pairs
        for (int i = 0; i < cnt - 2; i += 2) {
            for (int j = i + 2; j < cnt; j += 2) {
                if (allcheck(board, pos[i], pos[i + 1], pos[j], pos[j + 1])) {
                    delete[] pos;
                    return true;
                }
            }
        }

        //increase the check and free the pos array
        check++;
        delete[] pos;
    }
    return false;
}

bool suggestion(Cell_1** board, Position& p1, Position& p2) {
    const int maxPositions = BOARDHEIGHT * BOARDWIDTH;
    Position positions[maxPositions];
    int count = 0;

    // Iterate through each character from 'A' to 'Z'
    for (char check = 'A'; check <= 'Z'; ++check) {
        // Find positions of cells with the current character
        for (int i = 0; i < BOARDHEIGHT; ++i) {
            for (int j = 0; j < BOARDWIDTH; ++j) {
                if (board[i][j].c == check && board[i][j].valid) {
                    positions[count++] = {i, j};
                }
                if (count >= maxPositions) // Avoid exceeding array bounds
                    break;
            }
            if (count >= maxPositions) // Avoid exceeding array bounds
                break;
        }

        // Iterate through pairs of positions to check for a valid pair
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                // Check if there's a valid path between the pair of positions
                if (allcheck(board, positions[i].x, positions[i].y, positions[j].x, positions[j].y)) {
                    // If a valid pair is found, store the coordinates and return true
                    p1 = positions[i];
                    p2 = positions[j];
                    return true;
                }
            }
        }

        // Reset the count for the next character
        count = 0;
    }

    //if no valid pair left, return false
    return false;
}
