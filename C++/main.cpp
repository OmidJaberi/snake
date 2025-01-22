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
    switch(key)
    {
        case 'q':
            running = false;
            break;
        case ' ':
            if (!game.isRunning())
            {
                game.init();
                message = "";
            }
            else if (game.pause())
                message = "The game is paused. Press space to continue...";
            else
                message = "";
            break;
        case 'w':
            game.changeDir(std::make_pair(-1, 0));
            break;
        case 's':
            game.changeDir(std::make_pair(1, 0));
            break;
        case 'a':
            game.changeDir(std::make_pair(0, -1));
            break;
        case 'd':
            game.changeDir(std::make_pair(0, 1));
            break;
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
            if (!game.update())
                message = "Game over!!! Press SPACE to start over.";
            context.set_message(message);
            context.draw();
            last_time = now;
        }
    }
    return 0;
}
