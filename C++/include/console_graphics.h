#ifndef CONSOLE_GRAPHICS_H
#define CONSOLE_GRAPHICS_H

#include "graphics.h"

class ConsoleGraphics : public Graphics
{
private:
    const std::string snake = "🔵";
    const std::string food = "🍎";
    const std::string grass = "  ";
    void set_color();
    void reset_color();
    void clear();
public:
    ConsoleGraphics(SnakeGame& _game) : Graphics(_game) {};
    void draw() override;
};

#endif
