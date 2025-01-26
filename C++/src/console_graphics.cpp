#include "console_graphics.h"
#include <iostream>

void ConsoleGraphics::draw()
{
    clear();
    std::cout << "Score: " << game->getScore() << std::endl;

    set_color();
    std::cout << "\r╔";
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
    reset_color();

    if (message != "")
        std::cout << "\r" << message << std::endl;
}

void ConsoleGraphics::clear()
{
    printf("\e[1;1H\e[2J");
}

void ConsoleGraphics::set_color()
{
    std::cout << "\033[42m\033[37m";
}

void ConsoleGraphics::reset_color()
{
    std::cout << "\033[0m";
}    
