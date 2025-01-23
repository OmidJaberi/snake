#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

#include "snake_game.h"
#include "key_press.h"
#include "console_graphics.h"

std::atomic<bool> running{true};
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
	kp.add_listener(keyPressHandler, running);
    while (running)
    {
		if (!game.update())
			message = "Game over!!! Press SPACE to start over.";
        context.set_message(message);
		context.draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    return 0;
}
