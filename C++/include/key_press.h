#ifndef KEY_PRESS_H
#define KEY_PRESS_H

#include <functional>
#include <atomic>
#ifndef _WIN32
    #include <termios.h>
#endif

class KeyPress {
private:
    struct termios old_termios;
public:
    KeyPress();
    char getKey();
    void add_listener(std::function<void(int)>, std::atomic<bool> &running);
    ~KeyPress();
};

#endif
