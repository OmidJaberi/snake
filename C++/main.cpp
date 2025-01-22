#include <iostream>
#include <thread>
#include <chrono>
#include "snake_game.h"
#include "key_press.h"
#include "console_graphics.h"

bool running = true;
SnakeGame game(10, 10);
ConsoleGraphics context(game);
KeyPress kp;

std::string message;

void keyPressHandler(char key)
{
    if (key != 0)
    {
        if (key == 'q')
            running = false;
        else if (key == ' ')
        {
            if (game.pause())
                message = "The game is paused. Press space to continue...";
            else
                message = "";
        }
        else if (key == 'w')
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
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count() >= 150)
        {
            running = game.update();
            context.set_message(message);
            context.draw();
            last_time = now;
        }
    }

    if (!game.isRunning())
        std::cout << "\rGame over!!!" << std::endl;

    return 0;
}
