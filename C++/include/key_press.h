#ifndef KEY_PRESS_H
#define KEY_PRESS_H

#include <thread>
#include <functional>
#include <atomic>

class KeyPress {
public:
    KeyPress();
    char getKey();
    void add_listener(std::function<void(int)>, std::atomic<bool> &running);
    ~KeyPress();
};

#endif
