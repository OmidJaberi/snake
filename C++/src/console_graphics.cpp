#include "console_graphics.h"
#include <iostream>

void ConsoleGraphics::draw()
{
    clear();
    for (int i = 0; i < game->getHeight(); i++)
    {
        std::cout << "\r";
        for (int j = 0; j < game->getWidth(); j++)
            if (game->onSnake(std::make_pair(i, j)))
                std::cout << "# ";
            else if (game->onFood(std::make_pair(i, j)))
                std::cout << "@ ";
            else
                std::cout << ". ";
        std::cout << std::endl;
    }
    std::cout << "\rMessage: " << message << std::endl;
}

void ConsoleGraphics::clear()
{
    printf("\e[1;1H\e[2J");
}
