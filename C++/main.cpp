#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

#include "snake_game.h"
#include "key_press.h"
#include "console_graphics.h"

#define WIDTH 15
#define HEIGHT 10
#define SLEEP_MS 120

std::atomic<bool> running{true};
SnakeGame game(WIDTH, HEIGHT);
Graphics *graphics = new ConsoleGraphics(game);
KeyPress kp;

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
                graphics->set_message("");
            }
            else if (game.pause())
                graphics->set_message("The game is paused. Press space to continue...");
            else
                graphics->set_message("");
            break;
        case 'w':
        case 3:
            game.changeDir(std::make_pair(-1, 0));
            break;
        case 's':
        case 2:
            game.changeDir(std::make_pair(1, 0));
            break;
        case 'a':
        case 4:
            game.changeDir(std::make_pair(0, -1));
            break;
        case 'd':
        case 5:
            game.changeDir(std::make_pair(0, 1));
            break;
    }
}

int main()
{
    kp.add_listener(keyPressHandler, running);
    while (running)
    {
        if (!game.update())
            graphics->set_message("Game over!!! Press SPACE to start over.");
        graphics->draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
    }
    return 0;
}
