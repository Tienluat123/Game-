#include <Setting.h>

//move the cursor to a specific position on the console
void goToXY (int x, int y){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursor_pos;
    cursor_pos.X = x;
    cursor_pos.Y = y;
    SetConsoleCursorPosition(console, cursor_pos);
}

//set the visibility of the cursor in the console 
void setCursor (bool visible){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = visible;
    cursor.dwSize = 20;
    SetConsoleCursorInfo(console, &cursor);
}

//resize the game console 
void resizeWindow (int x, int y){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, x, y, TRUE);
}

//hide the scrollbar on the console
void hideScrollBar (){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);

    COORD new_screen_buffer_size;

    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

    SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}

//initialize the console 
void initWindow (int width, int length){
    resizeWindow(width, length);
    hideScrollBar();
    setCursor(0);
}