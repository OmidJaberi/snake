#include <iostream>
#include <thread>
#include <chrono>
#include "snake_game.h"
#include "key_press.h"

bool running = true;
SnakeGame game(10, 10);
KeyPress kp;

void draw()
{
    std::cout << "\e[1;1H\e[2J";
    for (int i = 0; i < game.getHeight(); i++)
    {
        std::cout << "\r";
        for (int j = 0; j < game.getWidth(); j++)
            if (game.onSnake(std::make_pair(i, j)))
                std::cout << "# ";
            else if (game.onFood(std::make_pair(i, j)))
                std::cout << "@ ";
            else
                std::cout << ". ";
        std::cout << std::endl;
    }
}

void keyPressHandler(char key)
{
    if (key != 0)
    {
        if (key == 'q')
            running = false;
        if (key == 'w')
            game.changeDir(std::make_pair(-1, 0));
        else if (key == 's')
            game.changeDir(std::make_pair(1, 0));
        else if (key == 'a')
            game.changeDir(std::make_pair(0, -1));
        else if (key == 'd')
            game.changeDir(std::make_pair(0, 1));
    }
}

int main()
{
    while (running)
    {
        keyPressHandler(kp.getKey());

        static auto last_time = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count() >= 300)
        {
            draw();
            running = game.update();
            last_time = now;
        }
    }

    if (!game.isRunning())
        std::cout << "\rGame over!!!" << std::endl;

    return 0;
}
