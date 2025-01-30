#include "key_press.h"
#include <thread>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

KeyPress::KeyPress()
{
#ifndef _WIN32
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
#endif
}

KeyPress::~KeyPress()
{
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
#endif
}

char KeyPress::getKey()
{
#ifdef _WIN32
    return _getch();
#else
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    return c;
#endif
}

void KeyPress::add_listener(std::function<void(int)> handler, std::atomic<bool> &running)
{
    std::thread([handler, this, &running]()
    {
        while (running)
        {
            char c = getKey();
            if (c != 0) handler(c);
        }
    }).detach();
}
