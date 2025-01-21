#include "console_graphics.h"
#include <iostream>

void ConsoleGraphics::draw()
{
    clear();
    std::cout << "╔";
    for (int i = 0; i < 2 * game->getWidth(); i++)
        std::cout << "═";
    std::cout << "╗" << std::endl;
    for (int i = 0; i < game->getHeight(); i++)
    {
        std::cout << "\r║";
        for (int j = 0; j < game->getWidth(); j++)
            if (game->onSnake(std::make_pair(i, j)))
                std::cout << snake;
            else if (game->onFood(std::make_pair(i, j)))
                std::cout << food;
            else
                std::cout << grass;
        std::cout << "║" << std::endl;
    }
    std::cout << "\r╚";
    for (int i = 0; i < 2 * game->getWidth(); i++)
        std::cout << "═";
    std::cout << "╝" << std::endl;
    if (message != "")
        std::cout << "\r" << message << std::endl;
}

void ConsoleGraphics::clear()
{
    printf("\e[1;1H\e[2J");
}
