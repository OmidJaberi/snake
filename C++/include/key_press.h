#ifndef KEY_PRESS_H
#define KEY_PRESS_H

#include <functional>
#include <atomic>
#ifndef _WIN32
    #include <termios.h>
#endif

class KeyPress {
private:
#ifndef _WIN32
    struct termios old_termios;
#endif
public:
    KeyPress();
    char getKey();
    void add_listener(std::function<void(int)>, std::atomic<bool> &running);
    ~KeyPress();
};

#endif
