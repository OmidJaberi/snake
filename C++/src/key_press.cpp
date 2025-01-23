#include "key_press.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

KeyPress::KeyPress()
{
#ifndef _WIN32
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
#endif
}

KeyPress::~KeyPress()
{
#ifndef _WIN32
    endwin();
#endif
}

char KeyPress::getKey()
{
#ifdef _WIN32
    return _getch();
#else
    return getch();
#endif
}

void KeyPress::add_listener(std::function<void(int)> handler, std::atomic<bool> &running)
{
    std::thread([handler, this, &running]()
    {
        while (running)
        {
            char c = getKey();
            handler(c);
        }
    }).detach();
}
