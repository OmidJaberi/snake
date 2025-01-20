#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include "snake_game.h"

class Graphics
{
    SnakeGame *game;
    std::string message;
public:
    Graphics(SnakeGame&);
    ~Graphics();
    void draw();
    void set_message(std::string msg) { message = msg; }
};

#endif
