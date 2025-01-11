#include <iostream>
#include <thread>
#include <chrono>
#include "snake_game.h"
#include "key_press.h"

SnakeGame game(10, 10);
KeyPress kp;

int main()
{
    bool running = true;
    while (running)
    {
        static auto last_time = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count() >= 300)
		{
            std::cout << "\e[1;1H\e[2J";
            for (int i = 0; i < 10; i++)
            {
                std::cout << "\r";
                for (int j = 0; j < 10; j++)
                    if (game.onSnake(std::make_pair(i, j)))
                        std::cout << "# ";
                    else if (game.onFood(std::make_pair(i, j)))
                        std::cout << "@ ";
                    else
                        std::cout << ". ";
                std::cout << std::endl;
            }
            running = game.update();
            last_time = now;
        }

        char key = kp.getKey();
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

    if (!game.isRunning())
        std::cout << "\rGame over!!!" << std::endl;

    return 0;
}
