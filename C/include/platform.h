#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

int getch(void);
#endif

#define COLOR_DEFAULT "\033[0m"
#define COLOR_MAP "\033[42m\033[37m"

void clear();

void set_color();

void reset_color();

#endif
