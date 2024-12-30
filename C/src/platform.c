#include "platform.h"
#include <stdio.h>

#ifndef _WIN32
int getch(void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\e[1;1H\e[2J");
#endif
}

void set_color()
{
#ifdef _WIN32
    return;
#else
    printf(COLOR_MAP);
#endif
}

void reset_color()
{
#ifdef _WIN32
    return;
#else
    printf(COLOR_DEFAULT);
#endif
}
