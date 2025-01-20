#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include "snake_game.h"

class Graphics
{
protected:
    SnakeGame *game;
    std::string message;
public:
    Graphics(SnakeGame& _game) : game(&_game) {};
    virtual ~Graphics() = default;
    virtual void draw() = 0;
    void set_message(std::string msg) { message = msg; }
};

#endif
