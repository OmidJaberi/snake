#include "key_press.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

KeyPress::KeyPress()
{
#ifdef _WIN32
    // No setup required for Windows
#else
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // Non-blocking input
    keypad(stdscr, TRUE);
#endif
}

KeyPress::~KeyPress()
{
#ifdef _WIN32
    // No cleanup required for Windows
#else
    def_prog_mode(); // Retain the screen without clearing
    //endwin();
#endif
}

char KeyPress::getKey()
{
#ifdef _WIN32
    if (_kbhit())
    {
        return _getch();
    }
    return 0;
#else
    int ch = getch();
    if (ch != ERR)
    {
        return ch;
    }
    return 0;
#endif
}
