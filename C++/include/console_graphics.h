#ifndef CONSOLE_GRAPHICS_H
#define CONSOLE_GRAPHICS_H

#include <string>
#include "graphics.h"
#include "snake_game.h"

class ConsoleGraphics : public Graphics
{
public:
    ConsoleGraphics(SnakeGame& _game) : Graphics(_game) {};
    void draw() override;
    void clear();
};

#endif
