#include "Checking.h"

//check if 2 chosen boxes is next to each other
bool nextCheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //vertical
    if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2)){
        if (a[x1][y1].c == a[x2][y2].c){
            return true;
        }
    }
    //horizontal
    if ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2)){
        if (a[x1][y1].c == a[x2][y2].c){
            return true;
        }
    }
    return false;
}

//check if if there is a line (sequence of consecutive valid cells) between two chosen boxes on a game board.
bool lineCheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //horizontal
    if (x1 == x2){
        int p, q, count = 0;
        //determines the starting and ending column indices
        if (y1 > y2){
            p = y2; q = y1;
        } else {
            p = y1; q = y2;
        }

        //count the valid boxes from starting to ending index
        for (int i = p; i <= q; i++){
            //check if current box is valid or not
            if (a[x1][i].valid){
                count++;
                //it finds two consecutive valid boxes, it returns false, indicating there is no line.
                if (count == 2)
                    return false;
            }
        }

        //If it finds only one valid box and the chosen boxes have opposite validity, return true, there is a line
        if ((count == 1) && ((!a[x1][y1].valid && a[x2][y2].valid) || (a[x1][y1].valid && !a[x2][y2].valid)))
            return true;
        //if there is no valid boxes, return true, there is a line
        else if (count == 0)
            return true;
        return false;
    }
    //vertical
    //vice versa to the horizontal 
    if (y1 == y2){
        int p, q, count = 0;
        if (x1 > x2){
            p = x2; q = x1;
        } else {
            p = x1; q = x2;
        }

        for (int i = p; i <= q; i++){
            if (a[i][y1].valid){
                count++;
                if (count == 2)
                    return false;
            }
        }

        if ((count == 1) && ((!a[x1][y1].valid && a[x2][y2].valid) || (a[x1][y1].valid && !a[x2][y2].valid)))
            return true;
        else if (count == 0)
            return true;
        return false;
    }
    return false;
}

//check if the 2 chosen boxes are connected in an I shape
bool Icheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //horizontal
     if (x1 == x2){
         int p, q;
         if (y1 > y2){
             p = y2; q = y1;
         } else {
             p = y1; q = y2;
         }

         for (int i = p + 1; i < q; i++){
             if (a[x1][i].valid)
                 return false;
         }

         return true;
     }
     //vertical
     if (y1 == y2){
         int p, q;
         if (x1 > x2){
             p = x2; q = x1;
         } else {
             p = x1; q = x2;
         }

         for (int i = p + 1; i < q; i++){
             if (a[i][y1].valid)
                 return false;
         }

         return true;
     }
     return false;
   /* if (lineCheck(a, x1, y1, x2, y2)){
        return true;
    } else {
        return false;
    }*/
}

//check if the 2 chosen boxes are connected in a L shape
bool Lcheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //if 2 boxes are horizontal or vertical, return false
    if (x1 == x2 || y1 == y2){
        return false;
    }

    bool l1, l2;
    //check if the top right corner of the potential L shape 
    //if it not valid, it considers two possible line patterns
    if (!a[x1][y2].valid){
        //line from x1, y1 to x1, y2 "------"
        l1 = lineCheck(a, x1, y1, x1, y2);
        //line from x2, y2 to x1, y2 "     |"
        l2 = lineCheck(a, x2, y2, x1, y2);

        //if 2 lines is valid, return true
        if (l1 && l2)
            return true;
    }
    //check if the the bottom right corner of the potential L shape
    //if it not valid, it considers two possible line patterns
    if (!a[x2][y1].valid){
        //line from x1, y1 to x2, y1 "|     "
        l1 = lineCheck(a, x1, y1, x2, y1);
        //line from x2, y2 to x2, y1 "------"
        l2 = lineCheck(a, x2, y2, x2, y1);

        //if 2 lines is valid, return true
        if (l1 && l2)
            return true;
    }

    return false;
}

//check if the 2 chosen boxes are connected in a Z shape
bool Zcheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //if 2 boxes are horizontal or vertical, return false
    if (x1 == x2 || y1 == y2){
        return false;
    }

    bool l1, l2, l3;
    int p, q;
    //find which is bigger x2 or y2 then assign the smaller for p and other for q
    if (y2 < x2){
        p = y2;
        q = x2;
    } else {
        p = x2;
        q = y2;
    }

    //check all possible horizontal Z shape 
    for (int i = p + 1; i < q; i++){
        //check the vertical line " |  "
        l3 = lineCheck(a, x1, i, x2, i);
        //if this line is valid, continue check 2 other lines
        if (l3){
            //check the first horizontal line from x1, y1 to the vertical line
            l1 = lineCheck(a, x1, y1, x1, i);
            //check the second horizontal line from x2, y2 to the vertical line
            l2 = lineCheck(a, x2, y2, x2, i);

            //if 2 lines are valid, return true
            if (l1 && l2)
                return true;
        }
    }

    //checking vertical Z shape is similar as checking horizontal Z shape
    //find the bigger one then assign the smaller one for p and the other for q 
    if (y1 < x1){
        p = y1;
        q = x1;
    } else {
        p = x1;
        q = y1;
    }

    //check all possible vertical Z shape
    for (int i = p + 1; i < q; i++){
        l3 = lineCheck(a, i, y1, i, y2);
        if (l3){
            l1 = lineCheck(a, x1, y1, i, y1);
            l2 = lineCheck(a, x2, y2, i, y2);

            if (l1 && l2)
                return true;
        }
    }

    return false;
}

//check if the 2 chosen boxes are connected in a U shape
bool Ucheck (Cell_1** a, int x1, int y1, int x2, int y2){
    //check if the 2 chosen boxes is at the border of the board
    if (((x1 == x2) && (x1 == 0 || x1 == BOARDHEIGHT - 1)) || ((y1 == y2) && (y1 == 0 || y1 == BOARDWIDTH - 1)))
        return true;
    
    bool l1, l2, l3;
    int p, q;
    //find which is bigger y1 or y2 then assign the smaller for p and other for q
    if (y1 > y2){
        p = y2;
        q = y1;
    } else {
        p = y1;
        q = y2;
    }
    //check the horizontal U shape 
    for (int i = 0; i < BOARDWIDTH; i++){
        //the vertical line must be out of the range (y1, y2)
        if (i <= p || i >= q){
            //check the vertical line of the shape
            l3 = lineCheck(a, x1, i, x2, i);
            //if the vertical line is valid
            if (l3){
                //continue check 2 horizontal lines
                //from (x1, y1) to the vertical line and from (x2, y2) to the vertical line
                l1 = lineCheck(a, x1, y1, x1, i);
                l2 = lineCheck(a, x2, y2, x2, i);
            } //if the vertical line is out of the board 
             else if (i == 0 || i == (BOARDWIDTH - 1)){
                //we just need to check 2 horizontal lines
                //continue check 2 horizontal lines
                //from (x1, y1) to the vertical line and from (x2, y2) to the vertical line
                l1 = lineCheck(a, x1, y1, x1, i);
                l2 = lineCheck(a, x2, y2, x2, i);
                if ((l1 && l2) || (l1 && y2 == i) || (y1 == i && l2))
                    return true;
            }
        }
    }

    //checking the vertical U shape is similar to checking the horizontal U shape
    if (x1 > x2) {
        p = x2;
        q = x1;
    } else {
        p = x1;
        q = x2;
    }
    //check the vertical U shape
    for (int i = 0; i < BOARDHEIGHT; i++) {
        //the horizontal line must be out of the range of (x1, x2)
        if (i <= p || i >= q) {
            //check the horizontal line
            l3 = lineCheck(a, i, y1, i, y2);
            //if the horizontal line is valid
            if (l3) {
                l1 = lineCheck(a, x1, y1, i, y1);
                l2 = lineCheck(a, x2, y2, i, y2);
                if (l1 && l2) {
                    return true;
                }
            } // if the horizontal line is out of the board
            else if (i == 0 || i == (BOARDHEIGHT - 1)) {
                l1 = lineCheck(a, x1, y1, i, y1);
                l2 = lineCheck(a, x2, y2, i, y2);
                if ((l1 && l2) || (l1 && x2 == i) || (x1 == i && l2)) {
                    return true;
                }
            }
        }
    }
    return false;
}

//check all the possible cases
bool allcheck (Cell_1** a, int x1, int y1, int x2, int y2){
    if (nextCheck(a, x1, y1, x2, y2))
        return true;
    else if (Icheck(a, x1, y1, x2, y2))
        return true;
    else if (Lcheck(a, x1, y1, x2, y2))
        return true;
    else if (Zcheck(a, x1, y1, x2, y2))
        return true;
    else if (Ucheck(a, x1, y1, x2, y2))
        return true;
    return false;
}

//check whether there exist valid pairs of cells with the same character
bool checkValidPairs(Cell_1** a){
    //create the first char 
    char check = 'A';

    //loop from A to Z
    while (check >= 'A' && check <= 'Z'){
        int count = 0;
        int* pos = new int[BOARDHEIGHT * BOARDWIDTH];

        // counts the occurrences of the current character check on the game board and stores their positions in the pos array.
        for (int i = 0; i < BOARDHEIGHT; i++){
            for (int j = 0; j < BOARDWIDTH; j++){
                if (a[i][j].c == check && a[i][j].valid){
                    pos[count++] = i;
                    pos[count++] = j;
                }
            }
        }

        //check the pair
        for (int i = 0; i < count - 2; i+= 2){
            for (int j = i + 2; j < count; j += 2){
                //checck a path, if there is a path, free the pos array and return true
                if (allcheck(a, pos[i], pos[i + 1], pos[j], pos[j + 1])){
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
